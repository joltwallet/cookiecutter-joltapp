//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"
#include "submenus.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_menu_about";
static const char TITLE[] = "About";


void {{cookiecutter.app_var_name}}_menu_about(jolt_gui_obj_t *btn, jolt_gui_event_t event) {
    if(jolt_gui_event.short_clicked == event){
        char buf[300];
        snprintf(buf, sizeof(buf), "Version: %d.%d.%d\nAuthor: {{cookiecutter.full_name}}\n",
                 {{cookiecutter.app_var_name|upper}}_VERSION.major,
                 {{cookiecutter.app_var_name|upper}}_VERSION.minor,
                 {{cookiecutter.app_var_name|upper}}_VERSION.patch
                 );
        ESP_LOGD(TAG, "Creating \"about\" screen");
        jolt_gui_scr_text_create(TITLE, buf);
    }
}
