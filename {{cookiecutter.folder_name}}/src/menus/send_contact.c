//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_menu_send_contact";
static const char TITLE[] = "Contacts";
(void) TAG;


void {{cookiecutter.app_var_name}}_menu_send_contacts(jolt_gui_obj_t *btn, jolt_gui_event_t event) {
    if(jolt_gui_event.short_clicked == event){
    }
}
