all: all-release

cmake-debug:
	mkdir -p build/debug
	cd build/debug && cmake -D CMAKE_BUILD_TYPE=Debug ../..

start-testnet:
	rm -rf bbs_testnet_data && \
	mkdir -p bbs_testnet_data && \
	./build/release/src/bbscoind --testnet --data-dir=bbs_testnet_data

start-testnet-wallet:
	rm -rf testnet.wallet && \
	rm -rf testnet.address && \
	./build/release/src/simplewallet --testnet --generate-new-wallet testnet && \
	./build/release/src/simplewallet --testnet --wallet-file testnet

start-testnet-walletd:
	rm -rf testnet_pool.wallet && \
	./build/release/src/walletd --testnet -w testnet_pool.wallet -g  && \
	./build/release/src/walletd --testnet -w testnet_pool.wallet

build-debug: cmake-debug
	cd build/debug && $(MAKE)

test-debug: build-debug
	cd build/debug && $(MAKE) test

all-debug: build-debug

cmake-release:
	mkdir -p build/release
	cd build/release && cmake -D CMAKE_BUILD_TYPE=Release ../..

build-release: cmake-release
	cd build/release && $(MAKE)

test-release: build-release
	cd build/release && $(MAKE) test

all-release: build-release

clean:
	rm -rf build

tags:
	ctags -R --sort=1 --c++-kinds=+p --fields=+iaS --extra=+q --language-force=C++ src contrib tests/gtest

.PHONY: all cmake-debug build-debug test-debug all-debug cmake-release build-release test-release all-release clean tags
