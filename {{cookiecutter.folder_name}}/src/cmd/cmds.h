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

/**
 * @brief Modify the contactbook
 *
 * Print the entire contact book ([Name] - [Address]):
 *     contact print [lower] [upper]
 * If lower is provided, it will print from that address to the end.
 * If upper is provided, it will print from lower to upper (inclusive).
 *
 * Remove a contact at index:
 *     contact delete [index]
 *
 * Add a contact to the end of the contact book
 *     contact add [name] [address]
 *
 * Insert a contact at index
 *     contact insert [index] [name] [address]
 *
 * Replace a contact at index
 *     contact update [index] [name] [address]
 *
 * Clear the entire contact book:
 *     contact clear
 *
 * @return 0 on success
 *
 */
int {{cookiecutter.app_var_name}}_cmd_contact(int argc, char **argv);

#endif
