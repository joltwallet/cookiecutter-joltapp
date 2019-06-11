#!/bin/bash -e
cp jolt_wallet/sdkconfig.defaults .
cp jolt_wallet/partitions.csv .
make defconfig >> /dev/null
./build.sh
