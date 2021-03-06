//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include <stddef.h>
#include "cmd/cmds.h"
#include "jolt_lib.h"
#include "menus/submenus.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_main";
static int console( int argc, const char **argv );

int japp_main( int argc, const char **argv )
{
    jolt_gui_obj_t *menu = NULL;
    if( 0 == argc ) {
        ESP_LOGD( TAG, "{{cookiecutter.app_name}} creating GUI" );
        const char title[] = "{{cookiecutter.app_name}}";
        menu               = jolt_gui_scr_menu_create( title );
        jolt_gui_scr_menu_add( menu, NULL, "Balance", {{cookiecutter.app_var_name}}_menu_balance);
        jolt_gui_scr_menu_add( menu, NULL, "Send", {{cookiecutter.app_var_name}}_menu_send_contact );
        jolt_gui_scr_menu_add( menu, NULL, "Select Account", {{cookiecutter.app_var_name}}_menu_select_account );
        jolt_gui_scr_menu_add( menu, NULL, "Address", {{cookiecutter.app_var_name}}_menu_address );
        jolt_gui_scr_menu_add( menu, NULL, "About", {{cookiecutter.app_var_name}}_menu_about );
        return (int)menu;
    }
    else {
        ESP_LOGD( TAG, "{{cookiecutter.app_var_name}} console command" );
        return console( argc, argv );
    }
}

static int console( int argc, const char **argv )
{
    /* Entry point for console commands.
     *
     * Design philosophy:
     *     * Commands should not rely on networking.
     *     * Commands should not export secrets.
     */
    esp_console_cmd_t cmd;
    jolt_cli_sub_t *subconsole = jolt_cli_sub_init();

    cmd = ( esp_console_cmd_t ) {
            .command = "address",
            .help    = "Get the {{cookiecutter.app_name}} address at derivation index or index range",
            .hint    = NULL,
            .func    = {{cookiecutter.app_var_name}}_cmd_address,
    };
    jolt_cli_sub_cmd_register( subconsole, &cmd );

    cmd = ( esp_console_cmd_t ) {
            .command = "contact",
            .help    = "Update {{cookiecutter.app_name}} contact book",
            .hint    = NULL,
            .func    = &jolt_app_cmd_contact,
    };
    jolt_cli_sub_cmd_register( subconsole, &cmd );

    ESP_LOGD( TAG, "Running %s", argv[0] );
    int res = jolt_cli_sub_cmd_run( subconsole, argc, argv );

    ESP_LOGD( TAG, "Freeing subconsole" );
    jolt_cli_sub_cmd_free( subconsole );

    ESP_LOGD( TAG, "App exiting with code %d", res );
    return res;
}
