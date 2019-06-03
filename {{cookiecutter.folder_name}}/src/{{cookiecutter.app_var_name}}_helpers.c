//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_helpers";

static cJSON *verify_json( cJSON *json );

cJSON *{{cookiecutter.app_var_name}}_get_json() {
    cJSON *json = jolt_json_read_app();
    return verify_json(json);
}

/**
 * @brief Ensure all the fields are present in the json config.
 * @param json Optional, if not provided, will create default json.
 * @return verified good json data. Will reboot if it cannot be produced.
 */
static cJSON *verify_json( cJSON *json ) {
#define EXIT_IF_NULL(x) save = true; if( NULL == x ) goto exit;
    bool save = false; // Write file at end of verification
    if( NULL == json ) {
        /* Create Default JSON */
        json = cJSON_CreateObject();
    }

    if( NULL == cJSON_Get(json, "index") ) {
        ESP_LOGW(TAG, "key %s not found", "index");
        EXIT_IF_NULL(cJSON_AddNumberToObject(json, "index", 0) );
    }
    if( NULL == cJSON_Get(json, "contacts") ) {
        ESP_LOGW(TAG, "key %s not found", "index");
        EXIT_IF_NULL( cJSON_AddArrayToObject(json, "contacts") );
    }
    if( save ) {
        jolt_json_write_app( json );
    }
    return json;
exit:
    assert( false ); // force a reboot
    jolt_json_del(json);
    return NULL;
#undef EXIT_IF_NULL
}

uint32_t {{cookiecutter.app_var_name}}_index_get( cJSON * json ) {
    uint32_t index=0;
    cJSON *obj;
    bool del_json = false;

    if( NULL == json ){
        json = {{cookiecutter.app_var_name}}_get_json();
        del_json = true;
    }
    obj = cJSON_GetObjectItemCaseSensitive(json, "index");
    if( NULL == obj ) {
        ESP_LOGW(TAG, "\"index\" key doesn't exist");
        return 0;
    }
    else {
        index = obj->valuedouble;
    }

    if( del_json ) {
        cJSON_Delete( json );
    }

    return index;
}

bool {{cookiecutter.app_var_name}}_index_set(cJSON *json, uint32_t index) {
    cJSON *obj;
    bool del_json = false;
    bool res = true;

    if( NULL == json ){
        json = {{cookiecutter.app_var_name}}_get_json();
        del_json = true;
    }
    obj = cJSON_GetObjectItemCaseSensitive(json, "index");
    if( NULL == obj ) {
        ESP_LOGW(TAG, "\"index\" key doesn't exist");
        res = false;
    }
    else {
        cJSON_SetNumberValue(obj, index);
    }

    jolt_json_write_app(json);
    if( del_json ) {
        cJSON_Delete( json );
    }

    return res;
}

bool {{cookiecutter.app_var_name}}_index_get_private( private_key_t private_key, const uint32_t index) {
    CONFIDENTIAL hd_node_t node;

    if( private_key == NULL ){
        return false;
    }

    vault_sem_take();
    if( vault_get_valid() ) {
        hd_node_copy(&node, vault_get_node());
    }
    else {
        vault_sem_give();
        return false;
    }
    vault_sem_give();

    hd_node_iterate(&node, index | HARDEN);
    
    {
        /* TODO: If your coin doesn't use a 256-bit PK, change this */
        assert( sizeof(private_key_t) == 32 );
        memcpy(private_key, &node.key, sizeof(uint256_t));
    }

    sodium_memzero(&node, sizeof(node));
    return true;
}

bool {{cookiecutter.app_var_name}}_index_get_private_public(private_key_t private_key, public_key_t public_key, const uint32_t index) {
    CONFIDENTIAL private_key_t private_key_local;
    if( private_key || public_key ) {
        if( !{{cookiecutter.app_var_name}}_index_get_private(private_key_local, index) ) {
            return false;
        }
        if( private_key ) {
            memcpy(private_key, private_key_local, sizeof(private_key_local));
        }
    }
    if( public_key ) {
        /* TODO: Derive Public Key from Private Key Here */
        // private_to_public(public_key_local, private_key_local);
    }
    sodium_memzero(private_key_local, sizeof(private_key_local));
    return true;
}

bool {{cookiecutter.app_var_name}}_index_get_public(public_key_t public_key, const uint32_t index) {
    return {{cookiecutter.app_var_name}}_index_get_private_public(NULL, public_key, index);
}

bool {{cookiecutter.app_var_name}}_index_get_private_public_address(private_key_t private_key, public_key_t public_key, char *address, const uint32_t index) {
    bool res = false;
    CONFIDENTIAL private_key_t private_key_local;
    public_key_t public_key_local;
    if( !{{cookiecutter.app_var_name}}_index_get_private_public(private_key_local, public_key_local, index) ) {
        goto err;
    }
    if( private_key ) {
        memcpy(private_key, private_key_local, sizeof(private_key_local));
    }
    if( public_key ) {
        memcpy(public_key, public_key_local, sizeof(public_key_local));
    }
    if( address ) {
        /* TODO: Derive Address from Public Key Here */
        //public_to_address(address, public_key_local);
        strcpy(address, "ADDRESS_PLACEHOLDER");
    }
    res = true;
err:
    sodium_memzero(private_key_local, sizeof(private_key_local));
    return res;
}

bool {{cookiecutter.app_var_name}}_index_get_address(char *address, const uint32_t index) {
    return {{cookiecutter.app_var_name}}_index_get_private_public_address(NULL, NULL, address, index);
}

bool {{cookiecutter.app_var_name}}_get_private(private_key_t private_key) {
    uint32_t index = {{cookiecutter.app_var_name}}_index_get( NULL );
    return {{cookiecutter.app_var_name}}_index_get_private(private_key, index);
}

bool {{cookiecutter.app_var_name}}_get_private_public(private_key_t private_key, public_key_t public_key) {
    uint32_t index = {{cookiecutter.app_var_name}}_index_get( NULL );
    return {{cookiecutter.app_var_name}}_index_get_private_public(private_key, public_key, index);
}

bool {{cookiecutter.app_var_name}}_get_public(public_key_t public_key) {
    return {{cookiecutter.app_var_name}}_get_private_public(NULL, public_key);
}

bool {{cookiecutter.app_var_name}}_get_private_public_address(private_key_t private_key, public_key_t public_key, char *address) {
    uint32_t index = {{cookiecutter.app_var_name}}_index_get( NULL );
    return {{cookiecutter.app_var_name}}_index_get_private_public_address(private_key, public_key, address, index);
}

bool {{cookiecutter.app_var_name}}_get_address(char *address) {
    return {{cookiecutter.app_var_name}}_get_private_public_address(NULL, NULL, address);
}
