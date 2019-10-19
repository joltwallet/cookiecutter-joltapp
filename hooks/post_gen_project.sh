#!/bin/bash -e
git submodule update --init --recursive
cp jolt_wallet/sdkconfig.defaults .
source jolt_wallet/export.sh
make defconfig >> /dev/null
make japp
