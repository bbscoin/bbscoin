// Copyright (c) 2012-2017, The CryptoNote developers, The Bytecoin developers. 2018 BBSCoin developers
//
// This file is part of BBSCoin.
//
// Bytecoin is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Bytecoin is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Bytecoin.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

namespace CryptoNote {
namespace parameters {

const uint32_t CRYPTONOTE_MAX_BLOCK_NUMBER                   = 500000000;
const size_t   CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                = 500000000;
const size_t   CRYPTONOTE_MAX_TX_SIZE                        = 1000000000;
const uint64_t CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX       = 0xe9;
const uint32_t CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW          = 60;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT            = 60 * 60 * 2;

const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW             = 60;
const size_t   BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW_V4          = 11;

// MONEY_SUPPLY - total number coins to be generated
const uint64_t MONEY_SUPPLY                                  = (uint64_t)(-1);
const unsigned EMISSION_SPEED_FACTOR                         = 18;
static_assert(EMISSION_SPEED_FACTOR <= 8 * sizeof(uint64_t), "Bad EMISSION_SPEED_FACTOR");

const size_t   CRYPTONOTE_REWARD_BLOCKS_WINDOW               = 100;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE     = 10000; //size of block (bytes) after which reward for block calculated using block size
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V3  = 100000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2  = 20000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1  = 10000;
const size_t   CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE;
const size_t   CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE        = 600;
const size_t   CRYPTONOTE_DISPLAY_DECIMAL_POINT              = 8;
const uint64_t MINIMUM_FEE                                   = uint64_t(100000);
const uint64_t DEFAULT_DUST_THRESHOLD                        = uint64_t(100000);

const uint16_t MINIMUM_MIXIN_V1                              = 0;
const uint16_t MAXIMUM_MIXIN_V1                              = 100;
const uint32_t MIXIN_LIMITS_V1_HEIGHT                        = 0; // Test from 0

const uint64_t DIFFICULTY_TARGET                             = 120; // seconds
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V2         = 7 * DIFFICULTY_TARGET;
const uint64_t CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT_V4         = 3 * DIFFICULTY_TARGET;
const uint64_t EXPECTED_NUMBER_OF_BLOCKS_PER_DAY             = 24 * 60 * 60 / DIFFICULTY_TARGET;
const size_t   DIFFICULTY_WINDOW                             = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;
const size_t   DIFFICULTY_WINDOW_V1                          = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;
const size_t   DIFFICULTY_WINDOW_V2                          = 70;
const size_t   DIFFICULTY_WINDOW_V3                          = 70;
const size_t   DIFFICULTY_WINDOW_V4                          = 60;
const size_t   DIFFICULTY_CUT                                = 60;  // timestamps to cut after sorting
const size_t   DIFFICULTY_CUT_V1                             = 60;
const size_t   DIFFICULTY_CUT_V2                             = 60;
const size_t   DIFFICULTY_CUT_V3                             = 60;
const size_t   DIFFICULTY_LAG                                = 15;  // !!!
const size_t   DIFFICULTY_LAG_V1                             = 15;
const size_t   DIFFICULTY_LAG_V2                             = 15;
const size_t   DIFFICULTY_LAG_V3                             = 0;
static_assert(2 * DIFFICULTY_CUT <= DIFFICULTY_WINDOW - 2, "Bad DIFFICULTY_WINDOW or DIFFICULTY_CUT");

const size_t   MAX_BLOCK_SIZE_INITIAL                        = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR         = 100 * 1024;
const uint64_t MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR       = 365 * 24 * 60 * 60 / DIFFICULTY_TARGET;
const uint64_t MAX_EXTRA_SIZE                                = 140000;

const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS     = 1;
const uint64_t CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS    = DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS;

const uint64_t CRYPTONOTE_MEMPOOL_TX_LIVETIME                = 60 * 60 * 24;     //seconds, one day
const uint64_t CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME = 60 * 60 * 24 * 7; //seconds, one week
const uint64_t CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL = 7;  // CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL * CRYPTONOTE_MEMPOOL_TX_LIVETIME = time to forget tx

const size_t   FUSION_TX_MAX_SIZE                            = CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT * 30 / 100;
const size_t   FUSION_TX_MIN_INPUT_COUNT                     = 12;
const size_t   FUSION_TX_MIN_IN_OUT_COUNT_RATIO              = 4;

const uint32_t KEY_IMAGE_CHECKING_BLOCK_INDEX                = 0;
const uint32_t UPGRADE_HEIGHT_V2                             = 60000;
const uint32_t UPGRADE_HEIGHT_V3                             = 72500;
const uint32_t UPGRADE_HEIGHT_V4                             = 180000;
const uint32_t UPGRADE_HEIGHT_V5                             = 202100;
const uint32_t UPGRADE_HEIGHT_V6                             = 205530;

const uint32_t UPGRADE_DIFFICULTY_HEIGHT_LWMA_V3             = 201500;
const uint64_t DIFFICULTY_BLOCKS_COUNT_LWMA_V3               = DIFFICULTY_WINDOW_V4 + 1;

const unsigned UPGRADE_VOTING_THRESHOLD                      = 1;               // percent
const uint32_t UPGRADE_VOTING_WINDOW                         = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
const uint32_t UPGRADE_WINDOW                                = EXPECTED_NUMBER_OF_BLOCKS_PER_DAY;  // blocks
static_assert(0 < UPGRADE_VOTING_THRESHOLD && UPGRADE_VOTING_THRESHOLD <= 100, "Bad UPGRADE_VOTING_THRESHOLD");
static_assert(UPGRADE_VOTING_WINDOW > 1, "Bad UPGRADE_VOTING_WINDOW");

const char     CRYPTONOTE_BLOCKS_FILENAME[]                  = "blocks.bbs";
const char     CRYPTONOTE_BLOCKINDEXES_FILENAME[]            = "blockindexes.bbs";
const char     CRYPTONOTE_POOLDATA_FILENAME[]                = "poolstate.bbs";
const char     P2P_NET_DATA_FILENAME[]                       = "p2pstate.bbs";
const char     MINER_CONFIG_FILE_NAME[]                      = "miner_conf.bbs.json";
} // parameters

const char     CRYPTONOTE_NAME[]                             = "BBSCoin";

const uint8_t  TRANSACTION_VERSION_1                         =  1;
const uint8_t  TRANSACTION_VERSION_2                         =  2;
const uint8_t  CURRENT_TRANSACTION_VERSION                   =  TRANSACTION_VERSION_1;
const uint8_t  BLOCK_MAJOR_VERSION_1                         =  1;
const uint8_t  BLOCK_MAJOR_VERSION_2                         =  2;
const uint8_t  BLOCK_MAJOR_VERSION_3                         =  3;
const uint8_t  BLOCK_MAJOR_VERSION_4                         =  4;
const uint8_t  BLOCK_MAJOR_VERSION_5                         =  5;
const uint8_t  BLOCK_MAJOR_VERSION_6                         =  6;
const uint8_t  BLOCK_MINOR_VERSION_0                         =  0;
const uint8_t  BLOCK_MINOR_VERSION_1                         =  1;

const size_t   BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT        =  10000;  //by default, blocks ids count in synchronizing
const size_t   BLOCKS_SYNCHRONIZING_DEFAULT_COUNT            =  100;    //by default, blocks count in blocks downloading
const size_t   COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT         =  1000;

const int      P2P_DEFAULT_PORT                              =  11204;
const int      RPC_DEFAULT_PORT                              =  21204;

const size_t   P2P_LOCAL_WHITE_PEERLIST_LIMIT                =  1000;
const size_t   P2P_LOCAL_GRAY_PEERLIST_LIMIT                 =  5000;

const size_t   P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE          = 16 * 1024 * 1024; // 16 MB
const uint32_t P2P_DEFAULT_CONNECTIONS_COUNT                 = 8;
const size_t   P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT     = 70;
const uint32_t P2P_DEFAULT_HANDSHAKE_INTERVAL                = 60;            // seconds
const uint32_t P2P_DEFAULT_PACKET_MAX_SIZE                   = 50000000;      // 50000000 bytes maximum packet size
const uint32_t P2P_DEFAULT_PEERS_IN_HANDSHAKE                = 250;
const uint32_t P2P_DEFAULT_CONNECTION_TIMEOUT                = 5000;          // 5 seconds
const uint32_t P2P_DEFAULT_PING_CONNECTION_TIMEOUT           = 2000;          // 2 seconds
const uint64_t P2P_DEFAULT_INVOKE_TIMEOUT                    = 60 * 2 * 1000; // 2 minutes
const size_t   P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT          = 5000;          // 5 seconds
const char     P2P_STAT_TRUSTED_PUB_KEY[]                    = "8f80f9a5a434a9f1510d13336228debfee9c918ce505efe225d8c94d045fa115";

const char* const SEED_NODES[] = { 
  "seed.bbscoin.xyz:11204", 
  "1.seed.bbscoin.xyz:11204", 
  "2.seed.bbscoin.xyz:11204", 
  "3.seed.bbscoin.xyz:11204", 
  "4.seed.bbscoin.xyz:11204", 
  "5.seed.bbscoin.xyz:11204", 
  "6.seed.bbscoin.xyz:11204", 
  "7.seed.bbscoin.xyz:11204", 
  "8.seed.bbscoin.xyz:11204", 
  "9.seed.bbscoin.xyz:11204", 
  "10.seed.bbscoin.xyz:11204", 
  "45.77.187.229:11204" 
};

struct CheckpointData {
  uint32_t index;
  const char* blockId;
};

const std::initializer_list<CheckpointData> CHECKPOINTS = {
    {54606, "18a155e5ae0a1b4992518698d1271382b566c49ed859540f3c81dc46fa5b89f6"},
    {60000, "dd02fb33f84443584e0432c28df61b372382c9a20542a5cb6b655a7932bd7d58"},
    {63600, "41c73113de2a37ae3a543c79083d4e509713a70a53ae5e7c70fcea641c396c56"},
    {64550, "8554549b78dc831fdca2b46cbef83729e0288a1997998c19fcb37e17164689c7"},
    {72580, "9fb75a9b219f884afc75c2fba08ac31ffe8ec5a188da3694edce9b094bd3741f"},
    {94730, "ec4e91d22603815601ece440e045c5f73da41b085468a1239757795a5887f3b4"},
    {129000, "65c713a8cb27b35ec028dbc47594e651f7b7c17faa2860d51564deaf1095a93f"},
    {154660, "03e4a9d3895af937b341f957c3bf303e873ec50ed4e09280fe4780a66c5f2645"},
    {174650, "4cc1db35a85a69af59fb3735ba2e9c86d20f072f41b3dd2726bcdd59a5c620d4"},
    {181751, "6d8090d695ee679fb0395a88e7145be8b075aeb2ca22187188f23d6f9f0d770a"},
    {181776, "e36d0b26a9ced41403361e916cad4d5480b1407f6a939dad8b2f8190d531c023"},
    {202078, "fd3e877abeed5f84a5276a956f70e862b34650f6aca675fa56572736347e77b0"},
    {202103, "01af7bec5cc4a20fd69f1fedcbce36fee0b9d43130d8ef7b00660cb4a0de4f48"},
    {221000, "21bb441697e1bd221403f16c3d15988711096714b58cb7ecb221a3f36733392e"},
    {237210, "8a2665082656ad5762d0c2940c863e23ade0e7654c6ff24cc88b89b1049e1bb0"},
    {320500, "71a770968fe9fed126f4b4e8cb9e04414299b78131b9a3d77c19f34137af0241"},
    {340700, "1f8e2817413dc67cac1469f040f9e097a9dadcd6e5d38f3cae5101a28025d192"},
    {460730, "7947f322f3739e1a62f98135a21a242edd8794243f6d35e28cb7714545a3b205"},
    {483290, "465d4248ffc8b2e96a98928d0cb87dca937e413a50580e2cc1174d9edaab9d60"},
    {560800, "f59c3300d8fa4aa93f2453d6753e8ad3a8fb31c536b9428c30b68142577da91f"},
    {590320, "a2d716934c62d8e4c3dc7cbace7bfacedef9d642843a5ffcafe76dd066606d49"}
};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS



