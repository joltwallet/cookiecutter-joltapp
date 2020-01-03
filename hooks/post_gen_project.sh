#!/bin/bash -e

git init
git add .
git submodule add git@github.com:joltwallet/jolt_wallet.git
git submodule update --init --recursive
git commit -a -m "Initial Cookiecutter Commit ( 0.1.2 )."
