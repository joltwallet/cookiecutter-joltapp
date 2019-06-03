//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include <stddef.h>
#include "jolt_lib.h"

#include "menus/submenus.h"
#include "cmd/cmds.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_main";
static int console(int argc, char **argv);
(void) TAG;

const jolt_version_t {{cookiecutter.app_var_name|upper}}_VERSION = {
    .major = 0,
    .minor = 1,
    .patch = 0,
    .release = JOLT_VERSION_DEV,
};

int app_main(int argc, char **argv) {
    jolt_gui_obj_t *menu = NULL;
    if( 0 == argc)  {
        const char title[] = "{{cookiecutter.app_var_name}}";
        menu = jolt_gui_scr_menu_create(title);
        jolt_gui_scr_menu_add(menu, NULL, "Balance", {{cookiecutter.app_var_name}}_menu_balance);
        jolt_gui_scr_menu_add(menu, NULL, "Send (contact)", {{cookiecutter.app_var_name}}_menu_contacts);
        jolt_gui_scr_menu_add(menu, NULL, "Select Account", {{cookiecutter.app_var_name}}_menu_select_account);
        jolt_gui_scr_menu_add(menu, NULL, "Address", {{cookiecutter.app_var_name}}_menu_address);
        jolt_gui_scr_menu_add(menu, NULL, "About", {{cookiecutter.app_var_name}}_menu_address);
        return (int)menu;
    }
    else {
        return console(argc, argv);
    }
}

static int console(int argc, char **argv) {
    /* Entry point for console commands.
     *
     * Design philosophy:
     *     * Commands should not rely on networking.
     *     * Commands should not export secrets.
     */
    esp_console_cmd_t cmd;
    jolt_cli_sub_t *subconsole = jolt_cli_sub_init();

    cmd = (esp_console_cmd_t) {
        .command = "address",
        .help = "Get the {{cookiecutter.app_name}} address at derivation index or index range",
        .hint = NULL,
        .func = {{cookiecutter.app_var_name}}_cmd_address,
    };
    jolt_cli_sub_cmd_register(subconsole, &cmd);

    cmd = (esp_console_cmd_t) {
        .command = "contact",
        .help = "Update {{cookiecutter.app_name}} contact",
        .hint = NULL,
        .func = {{cookiecutter.app_var_name}}_cmd_contact,
    };
    jolt_cli_sub_cmd_register(subconsole, &cmd);


    ESP_LOGD(TAG, "Running %s", argv[0]);
    int res = jolt_cli_sub_cmd_run(subconsole, argc, argv);

    ESP_LOGD(TAG, "Freeing subconsole");
    jolt_cli_sub_cmd_free(subconsole);

    ESP_LOGD(TAG, "App exiting with code %d", res);
    return res;
}
