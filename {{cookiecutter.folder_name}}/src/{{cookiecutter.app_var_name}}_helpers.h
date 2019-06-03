#ifndef JOLT_{{cookiecutter.app_var_name|upper}}_HELPERS_H__
#define JOLT_{{cookiecutter.app_var_name|upper}}_HELPERS_H__

#include "jolt_lib.h"

typedef unsigned char private_key_t[{{cookiecutter.private_key_bytes}}];
typedef unsigned char public_key_t[{{cookiecutter.private_key_bytes}}];

extern const jolt_version_t {{cookiecutter.app_var_name|upper}}_VERSION;

/**
 * @brief Loads and verifies the application configuration JSON
 * @return Config json
 */
cJSON *{{cookiecutter.app_var_name}}_get_json();

/**
 * @brief Gets the currently saved account index.
 * @param[in] json Optional input if json has been previously parsed
 * @return Account index; defaults/errors to 0.
 */
uint32_t {{cookiecutter.app_var_name}}_index_get( cJSON * json );

/**
 * @brief Sets and saved the provided account index
 * @param[in] json Optional input if json has been previously parsed
 * @param[in] index Index to save
 * @return true on success
 */
bool {{cookiecutter.app_var_name}}_index_set(cJSON *json, uint32_t index);

/**
 * @brief Get the private_key at given index
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] private_key Binary Private Key derived at index.
 * @param[in] index Index of account to retrieve.
 *
 * @return True on success, false otherwise.
 */
bool {{cookiecutter.app_var_name}}_index_get_private( private_key_t private_key, const uint32_t index);

/**
 * @brief Populates private_key and public_key at given index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] private_key Binary Private Key derived at index. May be NULL.
 * @param[out] public_key Binary Public Key derived at index. May be NULL.
 * @param[in] index Index of account to retrieve
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_index_get_private_public(private_key_t private_key, public_key_t public_key, const uint32_t index);

/**
 * @brief Populates public_key at given index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] public_key Binary Public Key derived at index.
 * @param[in] index Index of account to retrieve
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_index_get_public(public_key_t public_key, const uint32_t index);

/**
 * @brief Populates private_key, public_key, and address at given index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] private_key Binary Private Key derived at index. May be NULL.
 * @param[out] public_key Binary Public Key derived at index. May be NULL.
 * @param[out] address Address buffer to contain address. Assumed to be large enough. May be NULL.
 * @param[in] index Index of account to retrieve
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_index_get_private_public_address(private_key_t private_key, public_key_t public_key, char *address, const uint32_t index);

/**
 * @brief Populates address at given index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] address Address buffer to contain address. Assumed to be large enough. May be NULL.
 * @param[in] index Index of account to retrieve
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_index_get_address(char *address, const uint32_t index);

/**
 * @brief Get the private_key at current index
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] private_key Binary Private Key derived at index.
 *
 * @return True on success, false otherwise.
 */
bool {{cookiecutter.app_var_name}}_get_private(private_key_t private_key);

/**
 * @brief Populates private_key and public_key at current index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] private_key Binary Private Key derived at index. May be NULL.
 * @param[out] public_key Binary Public Key derived at index. May be NULL.
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_get_private_public(private_key_t private_key, public_key_t public_key);

/**
 * @brief Populates public_key at current index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] public_key Binary Public Key derived at index.
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_get_public(public_key_t public_key);

/**
 * @brief Populates private_key, public_key, and address at current index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] private_key Binary Private Key derived at index. May be NULL.
 * @param[out] public_key Binary Public Key derived at index. May be NULL.
 * @param[out] address Address buffer to contain address. Assumed to be large enough. May be NULL.
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_get_private_public_address(private_key_t private_key, public_key_t public_key, char *address);

/**
 * @brief Populates address at current index.
 *
 * Assumes that the vault has been externally refreshed 
 *
 * @param[out] address Address buffer to contain address. Assumed to be large enough. May be NULL.
 *
 * @return True on success, false otherwise
 */
bool {{cookiecutter.app_var_name}}_get_address(char *address);

#endif
