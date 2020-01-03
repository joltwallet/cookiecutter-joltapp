#ifndef JOLT_{{ cookiecutter.app_var_name | upper }}_SUBMENUS_H__
#define JOLT_{{ cookiecutter.app_var_name | upper }}_SUBMENUS_H__

#include "jolt_lib.h"

void {{cookiecutter.app_var_name}}_menu_about( jolt_gui_obj_t *btn, jolt_gui_event_t event );
void {{cookiecutter.app_var_name}}_menu_address( jolt_gui_obj_t *btn, jolt_gui_event_t event );
void {{cookiecutter.app_var_name}}_menu_send_contact( jolt_gui_obj_t *btn, jolt_gui_event_t event );
void {{cookiecutter.app_var_name}}_menu_select_account( jolt_gui_obj_t *btn, jolt_gui_event_t event );
void {{cookiecutter.app_var_name}}_menu_balance( jolt_gui_obj_t *btn, jolt_gui_event_t event );

#endif
