PROJECT_NAME := "{{cookiecutter.app_var_name}}"

EXTRA_COMPONENT_DIRS = \
        $(PROJECT_PATH)/src \
        $(PROJECT_PATH)/jolt_wallet/jolt_os/lvgl \
        $(PROJECT_PATH)/jolt_wallet/jolt_os \
        $(PROJECT_PATH)/jolt_wallet/components


CFLAGS += \
        -Werror \
        -DJOLT_APP

include $(IDF_PATH)/make/project.mk
