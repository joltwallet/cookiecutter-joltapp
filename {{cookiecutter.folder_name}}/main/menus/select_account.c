//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"

static const char TAG[]   = "{{cookiecutter.app_var_name}}_menu_select_account";
static const char TITLE[] = "Account";

/* Stores the selected index to config */
static void index_cb( jolt_gui_obj_t *btn_sel, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) {
        int32_t index = jolt_gui_scr_menu_get_btn_index( btn_sel );
        if( index >= 0 ) {
            ESP_LOGI( TAG, "Saving index %d", index );
            {{cookiecutter.app_var_name}}_index_set( NULL, index );
        }
        else {
            ESP_LOGE( TAG, "Selected button not found in list" );
        }
        jolt_gui_scr_del( btn_sel );
    }
}

static void select_account_cb( void *dummy )
{
    uint32_t index = {{cookiecutter.app_var_name}}_index_get( NULL );
    ESP_LOGI( TAG, "Current {{cookiecutter.app_name}} Address Derivation Index: %d", index );

    jolt_gui_obj_t *menu = jolt_gui_scr_menu_create( TITLE );
    jolt_gui_obj_t *sel  = NULL;

    for( uint8_t i = 0; i <
                        CONFIG_JOLT_{{cookiecutter.app_var_name | upper}}_CONTACTS_MAX;
         i++ ) {
        char address[ADDRESS_BUF_LEN];
        char buf[ADDRESS_BUF_LEN + 16];
        if( !{{cookiecutter.app_var_name}}_index_get_address( address, i ) ) {
            strlcpy( buf, "ERROR", sizeof( buf ) );
        }
        else {
            snprintf( buf, sizeof( buf ), "%d. %s", i + 1, address );
        }
        jolt_gui_obj_t *btn = jolt_gui_scr_menu_add( menu, NULL, buf, index_cb );
        if( i == index || 0 == i ) { sel = btn; }
    }
    jolt_gui_scr_menu_set_btn_selected( menu, sel );
}

void {{cookiecutter.app_var_name}}_menu_select_account( jolt_gui_obj_t *btn, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) { vault_refresh( NULL, select_account_cb, NULL ); }
}
