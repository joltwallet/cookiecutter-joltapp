#!/bin/bash -e
# App Specific Parameters
APP_BASENAME="{{cookiecutter.app_name|replace(' ','_')}}"
COIN_PATH="{{cookiecutter.coin_path}}"
BIP32_KEY="{{cookiecutter.bip32_key}}"
ELF2JELF="jolt_wallet/elf2jelf/elf2jelf.py"
PYTHONBIN="python3"

# e.g. -Wl, build/<component>/lib<component>.a
ADDITIONAL_LINKER_ARGS=""

# Convert names to absolute paths and stuff
ELF_BIN_NAME="${APP_BASENAME}.elf"
JELF_BIN_NAME="${APP_BASENAME}.jelf"
JELF_BIN_COMPRESSED_NAME="${JELF_BIN_NAME}.gz"
ELF_BIN_NAME="$(realpath $ELF_BIN_NAME)"
JELF_BIN_NAME="$(realpath $JELF_BIN_NAME)"
JELF_BIN_COMPRESSED_NAME="$(realpath $JELF_BIN_COMPRESSED_NAME)"
ELF2JELF="$(realpath $ELF2JELF)"

SIGNING_KEY_FILE="signing_key"
if [ -f "$SIGNING_KEY_FILE" ]; then
    SIGNING_KEY=`cat $SIGNING_KEY_FILE`
else
    SIGNING_KEY="ABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABABAB"
fi

# Put some space on the console for easier debugging
printf "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"

# OS specific configurations
if [[ "$OSTYPE" == "linux-gnu" ]]; then
    # ...
    echo "linux-gnu detected."
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # Mac OSX
    echo "MacOS detected."
elif [[ "$OSTYPE" == "cygwin" ]]; then
    # POSIX compatibility layer and Linux environment emulation for Windows
    echo "cygwin detected."
elif [[ "$OSTYPE" == "msys" ]]; then
    # Lightweight shell and GNU utilities compiled for Windows (part of MinGW)
    echo "msys detected."
elif [[ "$OSTYPE" == "win32" ]]; then
    # I'm not sure this can happen.
    echo "win32 detected."
elif [[ "$OSTYPE" == "freebsd"* ]]; then
    # ...
    echo "freeBSD detected."
else
    # Unknown.
    echo "Error detecting operating system."
fi

if [ -f "${ELF_BIN_NAME}" ] ; then
    rm "${ELF_BIN_NAME}"
fi
if [ -f "${JELF_BIN_NAME}" ] ; then
    rm "${JELF_BIN_NAME}"
fi
if [ -f "${JELF_BIN_COMPRESSED_NAME}" ] ; then
    rm "${JELF_BIN_COMPRESSED_NAME}"
fi

make app -j15

if xtensa-esp32-elf-gcc -Wl,-static -nostartfiles -nodefaultlibs -nostdlib -Os \
    -ffunction-sections -fdata-sections -Wl,--gc-sections \
    -Wl,-T${IDF_PATH}/components/esp_rom/esp32/ld/esp32.rom.newlib-nano.ld \
    -Wl,-T${IDF_PATH}/components/esp_rom/esp32/ld/esp32.rom.ld -s -o "${ELF_BIN_NAME}" \
    -Wl,-r \
    -Wl,-eapp_main \
    -Wl,--warn-unresolved-symbols \
    build/src/libsrc.a \
    ${ADDITIONAL_LINKER_ARGS} \
    ;
then
    echo "Successfully assembled ELF"
else
    echo "Failed assembling ELF"
    exit 1;
fi

# Remove unneccessary sections
xtensa-esp32-elf-objcopy --remove-section=.comment \
         --remove-section=.xtensa.info \
         --remove-section=.xt.prop \
         --remove-section=.rela.xt.prop \
         --remove-section=.xt.lit \
         --remove-section=.rela.xt.lit \
         --remove-section=.text \
         "$ELF_BIN_NAME"

#######################
# Convert ELF to JELF #
#######################
# todo: signing key argument
if $PYTHONBIN $ELF2JELF  "$ELF_BIN_NAME" \
    --output "$JELF_BIN_NAME" \
    --coin "$COIN_PATH" \
    --bip32key "$BIP32_KEY" \
    ;
then
    echo "Successfully converted ELF to JELF"
else
    echo "Failed converting ELF to JELF"
    exit 1;
fi
