SHELL := /bin/bash

test:
	# Tests if it builds
	rm -rf my_jolt_app_joltapp/
	cookiecutter --no-input --overwrite-if-exists .
	cd my_jolt_app_joltapp/jolt_wallet; \
		source export.sh; \
		cd ..; \
		make defconfig; \
		make japp

install:
	pip3 install -r requirements.txt
