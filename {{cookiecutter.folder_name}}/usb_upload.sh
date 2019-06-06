#!/bin/bash -e
python3 jolt_wallet/pyutils/usb_upload.py {{cookiecutter.app_name|replace(' ','_')}}.jelf
