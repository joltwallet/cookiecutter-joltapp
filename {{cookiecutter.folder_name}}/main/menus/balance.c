//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"
#include "{{cookiecutter.app_var_name}}_network.h"

static const char TAG[]   = "{{cookiecutter.app_var_name}}_menu_balance";
static const char TITLE[] = "{{cookiecutter.app_name}} Balance";

void {{cookiecutter.app_var_name}}_menu_balance_cb( void *dummy )
{
    ESP_LOGD( TAG, "(%d) Creating preloading screen", __LINE__ );
    jolt_gui_obj_t *scr;
    scr = jolt_gui_scr_preloading_create( TITLE, "Contacting Server" );
    if( NULL == scr ) { return; }
    /* TODO: Call a network command to get balance */
    jolt_gui_scr_set_event_cb( scr, jolt_gui_event_del );
}

void {{cookiecutter.app_var_name}}_menu_balance( jolt_gui_obj_t *btn, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) {
        ESP_LOGD( TAG, "Refreshing Vault" );
        vault_refresh( NULL, {{cookiecutter.app_var_name}}_menu_balance_cb, NULL );
    }
}
