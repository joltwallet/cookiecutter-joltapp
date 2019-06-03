//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_menu_balance";
static const char TITLE[] = "{{cookiecutter.app_name}} Balance";
(void) TAG;

void {{cookiecutter.app_var_name}}_menu_balance_cb( void *dummy ) {
    jolt_gui_obj_t *scr = jolt_gui_scr_preloading_create(TITLE, "Contacting Server");

    char address[ADDRESS_BUF_LEN];
    {{cookiecutter.app_var_name}}_get_address( address );
    {{cookiecutter.app_var_name}}_network_frontier_block( address, frontier_cb, NULL, scr );
}

void {{cookiecutter.app_var_name}}_menu_balance( jolt_gui_obj_t *btn, jolt_gui_event_t event ) {
    if( jolt_gui_event.short_clicked == event ){
        vault_refresh(NULL, {{cookiecutter.app_var_name}}_menu_balance_cb, NULL);
    }
}
