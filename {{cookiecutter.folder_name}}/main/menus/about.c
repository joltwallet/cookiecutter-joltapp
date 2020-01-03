//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"

static const char TAG[]   = "{{cookiecutter.app_var_name}}_menu_about";
static const char TITLE[] = "About";

void {{cookiecutter.app_var_name}}_menu_about( jolt_gui_obj_t *btn, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) {
        char buf[300];
        snprintf( buf, sizeof( buf ), "Version: %d.%d.%d\nAuthor: {{cookiecutter.full_name}}\n",
                  CONFIG_APP_VERSION_MAJOR, CONFIG_APP_VERSION_MINOR, CONFIG_APP_VERSION_PATCH );
        ESP_LOGD( TAG, "Creating \"about\" screen" );
        jolt_gui_scr_text_create( TITLE, buf );
    }
}
