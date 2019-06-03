//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_menu_address";
static const char TITLE[] = "{{cookiecutter.app_name}} Address";
(void) TAG;

static void menu_{{cookiecutter.app_var_name}}_address_cb( void *dummy ) {
    char buf[120]; // shared buffer for text-address and QR data
    uint256_t public_key;
    jolt_gui_obj_t *scr = NULL;
    jolt_err_t err;

    uint32_t index;
    index = {{cookiecutter.app_var_name}}_index_get( cJSON * json );

    scr = jolt_gui_scr_scroll_create(TITLE);
    if( NULL == scr ) {
        goto exit;
    }
    assert({{cookiecutter.app_var_name}}_index_get_address(buf, index));

    /* Display Address in monospace text */
    jolt_gui_scr_scroll_add_monospace_text(scr, buf); //todo; break up into even lines

    /* Display address as a QR code */
    jolt_gui_scr_scroll_add_qr(scr, buf, strlen(buf));

    return;

exit:
    if( NULL != scr ) {
        jolt_gui_obj_del(scr);
    }
}

void {{cookiecutter.app_var_name}}_menu_address( jolt_gui_obj_t *btn, jolt_gui_event_t event ) {
    if(jolt_gui_event.short_clicked == event){
        vault_refresh(NULL, menu_{{cookiecutter.app_var_name}}_address_cb, NULL);
    }
}
