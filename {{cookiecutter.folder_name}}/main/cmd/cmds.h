#ifndef JOLT_{{cookiecutter.app_var_name|upper}}_CMDS_H__
#define JOLT_{{cookiecutter.app_var_name|upper}}_CMDS_H__

/**
 * @brief Print info about the app
 *
 * Takes no arguments
 */
int {{cookiecutter.app_var_name}}_cmd_about(int argc, char ** argv);

/**
 * @brief Print the Addresses of given index
 * Optionally takes a second argument to print the inclusive range.
 */
int {{cookiecutter.app_var_name}}_cmd_address(int argc, char ** argv);

#endif
