#!/bin/bash -e
cd jol_wallet && git submodule update --init && cd ..
cp jolt_wallet/sdkconfig.defaults .
cp jolt_wallet/partitions.csv .
make defconfig >> /dev/null

