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
 * If lower is provided and upper is not, it will print that address.
 * If lower and upper is provided, it will print from lower to upper (exclusive).
 *
 * Remove a contact at index:
 *     contact delete [index]
 *     *not yet implemented*
 *
 * Add a contact to the end of the contact book
 *     contact add [name] [address]
 *
 * Insert a contact at index
 *     contact insert [index] [name] [address]
 *     *not yet implemented*
 *
 * Replace a contact at index
 *     contact update [index] [name] [address]
 *     *not yet implemented*
 *
 * Clear the entire contact book:
 *     contact clear
 *     *not yet implemented*
 *
 * @return 0 on success
 *
 */
int {{cookiecutter.app_var_name}}_cmd_contact(int argc, char **argv);

#endif
