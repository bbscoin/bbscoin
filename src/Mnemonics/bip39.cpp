// Copyright (c) 2018 ciband (https://github.com/ciband/bip39). 2018 - 2019 BBSCoin developers
//
// This file is part of BBSCoin.
//
// You should have received a copy of the GNU Lesser General Public License
// along with BBSCoin.  If not, see <http://www.gnu.org/licenses/>.

#include "bip39.h"
#include "english.h"
#include "spanish.h"
#include "japanese.h"
#include "italian.h"
#include "french.h"
#include "korean.h"
#include "chinese_simplified.h"
#include "chinese_traditional.h"

#include "picosha2.h"

#include <vector>
#include <random>
#include <climits>
#include <algorithm>
#include <functional>
#include <cassert>
#include <iostream>

namespace BIP39 {

using random_bytes_engine = std::independent_bits_engine<
    std::default_random_engine, 16, uint16_t>;

const char* const * get_string_table(language lang) {
	switch (lang) {
	case language::en: return english_table;
    case language::es: return spanish_table;
    case language::ja: return japanese_table;
    case language::it: return italian_table;
    case language::fr: return french_table;
    case language::ko: return korean_table;
    case language::zh_Hans: return chinese_simplified_table;
    case language::zh_Hant: return chinese_traditional_table;

	default:
		assert("error unsupported language");
		return nullptr;
	};
}

namespace {

uint8_t bip39_shift(size_t bit)
{
    return (1 << (BYTE_BITS - (bit % BYTE_BITS) - 1));
}

int get_word_index(const char* const * const lexicon, const std::string& word) {
    for (auto i = 0u; i < NUM_BIP39_WORDS; ++i) {
        char w[MAX_BIP39_WORD_OCTETS] = {};
        strcpy_P(w, (char*)pgm_read_ptr_far(&(lexicon[i]))); // NOLINT
        if (strcmp(w, word.c_str()) == 0) {
            return i;
        }
    }
    return -1;
}

void append_checksum_bits(std::vector<uint8_t>& entropyBuffer) {
    const auto ENT = entropyBuffer.size() * BYTE_BITS;
    const auto CS = ENT / 32u;

    picosha2::hash256_one_by_one hasher;
    hasher.process(entropyBuffer.begin(), entropyBuffer.end());
    hasher.finish();
    std::vector<uint8_t> hash(picosha2::k_digest_size);
    hasher.get_hash_bytes(hash.begin(), hash.end());
    const auto checksum_byte_count = std::min((CS / BYTE_BITS) + 1, picosha2::k_digest_size);
    for (auto i = 0u; i < checksum_byte_count; ++i) {
        entropyBuffer.push_back(hash[i]);
    }
}

}

word_list create_mnemonic(std::vector<uint8_t>& entropy, language lang /* = language::en */) {
    const size_t entropy_bits = (entropy.size() * BYTE_BITS);
    const size_t check_bits = (entropy_bits / ENTROPY_BIT_DIVISOR);
    const size_t total_bits = (entropy_bits + check_bits);
    const size_t word_count = (total_bits / BITS_PER_WORD);

    append_checksum_bits(entropy);

    size_t bit = 0;
    const auto lexicon = get_string_table(lang);
    word_list words;
    for (size_t i = 0; i < word_count; i++)
    {
        size_t position = 0;
        for (size_t loop = 0; loop < BITS_PER_WORD; loop++)
        {
            bit = (i * BITS_PER_WORD + loop);
            position <<= 1;

            const auto byte = bit / BYTE_BITS;

            if ((entropy[byte] & bip39_shift(bit)) > 0)
            {
                position++;
            }
        }

        assert(position < DICTIONARY_SIZE);
        char word[MAX_BIP39_WORD_OCTETS] = {};
        strcpy_P(word, (char*)pgm_read_ptr_far(&(lexicon[position]))); // NOLINT
        words.add(word);
    }
    return words;
}

word_list generate_mnemonic(entropy_bits_t entropy /* = entropy_bits::_128 */, language lang /* = language::en */) {
    const auto entropy_bits = static_cast<entropy_bits_int_type>(entropy);
    assert(entropy_bits % (MNEMONIC_SEED_MULTIPLE * BYTE_BITS) == 0);

    const auto check_bits = (entropy_bits / ENTROPY_BIT_DIVISOR);
    const auto total_bits = (entropy_bits + check_bits);
    const auto word_count = (total_bits / BITS_PER_WORD);

    assert((total_bits % BITS_PER_WORD) == 0);
    assert((word_count % MNEMONIC_WORD_MULTIPLE) == 0);

    random_bytes_engine rbe;
    std::vector<uint8_t> data(entropy_bits / BYTE_BITS);
    std::generate(begin(data), end(data), [&rbe]() { return static_cast<uint8_t>(std::ref(rbe)()); });
    return create_mnemonic(data, lang);
}

std::vector<uint8_t> decode_mnemonic(const word_list& mnemonic, const std::string& password /* = "" */) {
    return std::vector<uint8_t>();
}

bool valid_mnemonic(const word_list& mnemonic, language lang, std::vector<uint8_t>& data) {
    const auto word_count = mnemonic.size();
    
    if ((word_count % MNEMONIC_WORD_MULTIPLE) != 0) {
        return false;
    }

    const auto total_bits = BITS_PER_WORD * word_count;
    const auto check_bits = total_bits / (ENTROPY_BIT_DIVISOR + 1);
    const auto entropy_bits = total_bits - check_bits;

    assert((entropy_bits % BYTE_BITS) == 0);

    size_t bit = 0;
    std::vector<uint8_t> new_data((total_bits + BYTE_BITS - 1) / BYTE_BITS, 0);
    const auto lexicon = get_string_table(lang);

    for (const auto& word : mnemonic)
    {
        const auto position = get_word_index(lexicon, word);
        if (position == -1) { return false; }

        for (size_t loop = 0; loop < BITS_PER_WORD; loop++, bit++)
        {
            if ((position & (1 << (BITS_PER_WORD - loop - 1))) != 0)
            {
                const auto byte = bit / BYTE_BITS;
                new_data[byte] |= bip39_shift(bit);
            }
        }
    }

    new_data.resize(entropy_bits / BYTE_BITS);
    data = new_data;
    const auto new_mnemonic = create_mnemonic(data, lang);
    return std::equal(new_mnemonic.begin(), new_mnemonic.end(), mnemonic.begin());
}

bool convert_to_secret_key(std::string& mnemonic_word, language lang, Crypto::SecretKey& secretKey) {
	char delimiter = ' ';
	std::vector<uint8_t> vecSecretKey;

	word_list mnemonic = BIP39::split(mnemonic_word, delimiter);
	bool ret = valid_mnemonic(mnemonic, lang, vecSecretKey);
	if (!ret) {
		return ret;
	}

	for (int i = 0; i < 32; ++i) {
		secretKey.data[i] = vecSecretKey[i];
	}
	return true;
}

bool convert_from_secret_key(std::string& mnemonic_word, language lang, Crypto::SecretKey& secretKey) {
	std::vector<uint8_t> vecSecretKey;

	for (int i = 0; i < 32; ++i) {
		vecSecretKey.push_back(secretKey.data[i]);
	}

	word_list mnemonic = create_mnemonic(vecSecretKey, lang);
	mnemonic_word = mnemonic.to_string();

	if (mnemonic_word.empty()) {
		return false;
	}

	return true;
}
}