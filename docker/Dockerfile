FROM ubuntu:18.04

RUN set -ex; \
    \
    apt-get update; \
    apt-get install -y build-essential libboost1.65-all-dev git cmake; \ 
    git clone https://github.com/bbscoin/bbscoin.git; \
    cd bbscoin; \
    make -j$(nproc); \
    apt-get remove -y build-essential libboost1.65-all-dev git cmake; \
    apt-get autoremove -y; \
    apt-get install -y \
      libboost-system1.65 \
      libboost-filesystem1.65 \
      libboost-thread1.65 \
      libboost-date-time1.65 \
      libboost-chrono1.65 \
      libboost-regex1.65 \
      libboost-serialization1.65 \
      libboost-program-options1.65; \
    mkdir -p /usr/local/bin; \
    cp build/release/src/bbscoind build/release/src/connectivity_tool build/release/src/miner build/release/src/simplewallet build/release/src/walletd /usr/local/bin; \
    cd ..; \
    rm -rf ./bbscoin
   
EXPOSE 11204
EXPOSE 21204

VOLUME ["/root/.BBSCoin"]

ENTRYPOINT [ "/usr/local/bin/bbscoind" ]
