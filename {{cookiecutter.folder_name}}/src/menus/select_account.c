//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_menu_select_account";
static const char TITLE[] = "{{cookiecutter.app_var_name}} Account";
(void) TAG;


void {{cookiecutter.app_var_name}}_menu_select_account(jolt_gui_obj_t *btn, jolt_gui_event_t event) {
    if(jolt_gui_event.short_clicked == event){
    }
}
