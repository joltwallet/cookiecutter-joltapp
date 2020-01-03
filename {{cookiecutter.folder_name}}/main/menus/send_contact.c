//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "submenus.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"
#include "{{cookiecutter.app_var_name}}_network.h"

static const char TAG[]        = "{{cookiecutter.app_var_name}}_menu_send_contact";
static const char TITLE[]      = "Contacts";
static const char TITLE_SEND[] = "Send";

typedef struct {
    struct {
        jolt_gui_obj_t *contacts; /**< Contacts list */
        jolt_gui_obj_t *progress; /**< Displays progress bar of processing transaction*/
        jolt_gui_obj_t *entry;    /**< Screen to enter send amount */
        jolt_gui_obj_t *error;    /**< DIsplay error */
    } scr;

    struct {
        cJSON *root;            /**< Root JSON config node */
        cJSON *contacts;        /**< Contacts array node */
        uint32_t account_index; /**< Local account derivation index */
    } cfg;

    int8_t contact_index; /**< Selected contact index */

} send_obj_t;

static send_obj_t *d = NULL; /* Send Context */

/********************
 * STATIC FUNCTIONS *
 ********************/

static void cleanup_complete( void *param );
static void cleanup_complete_cb( jolt_gui_obj_t *dummy, jolt_gui_event_t event );
static void processing_cb_1( jolt_gui_obj_t *num_scr, jolt_gui_event_t event );
static void processing_cb_2( void *param );

/**
 * @brief cleanup the entire send context.
 *
 * Called upon exit, completion, OOM-errors, or corrupt data.
 */
static void cleanup_complete( void *param )
{
    /* Screen cleanup */
    if( d->scr.contacts ) jolt_gui_obj_del( d->scr.contacts );
    if( d->scr.progress ) jolt_gui_obj_del( d->scr.progress );
    if( d->scr.entry ) jolt_gui_obj_del( d->scr.entry );
    if( d->scr.error ) jolt_gui_obj_del( d->scr.error );

    /* Config JSON cleanup */
    if( d->cfg.root ) jolt_json_del( d->cfg.root );

    /* Context Deletion */
    free( d );
    d = NULL;
}

/**
 * @brief cleanup the entire send context.
 *
 * Called upon exit, completion, OOM-errors, or corrupt data.
 */
static void cleanup_complete_cb( jolt_gui_obj_t *dummy, jolt_gui_event_t event )
{
    if( jolt_gui_event.cancel == event ) { cleanup_complete( NULL ); }
}

/**
 * @brief Prompts for PIN to get account access
 */
static void processing_cb_1( jolt_gui_obj_t *num_scr, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) {
        /* populates dst_address */
        cJSON *contact, *json_address;

        contact = cJSON_GetArrayItem( d->cfg.contacts, d->contact_index );
        if( NULL == contact ) {
            ESP_LOGE( TAG, "Index out of range" );
            goto exit;
        }

        {
            char *dst_address;
            json_address = cJSON_Get( contact, "address" );
            if( NULL == json_address ) {
                ESP_LOGE( TAG, "Contact didn't have field \"address\"" );
                goto exit;
            }
            dst_address = cJSON_GetStringValue( json_address );
            ESP_LOGD( TAG, "Contact address: %s", dst_address );
        }

        /* Populate transaction Amount. */
        /* TODO: Translate the value from num_scr to an appropriate format.
         * Store the results in d. */

        /* Prompt for pin to derive public address */
        vault_refresh( NULL, processing_cb_2, NULL );
    }
    else if( jolt_gui_event.cancel == event ) {
        jolt_gui_obj_del( d->scr.entry );
        d->scr.entry = NULL;
    }
    return;

exit:
    cleanup_complete( NULL );
    return;
}

/**
 * @brief Creates loading screen, perform network action
 */
static void processing_cb_2( void *param )
{
    char my_address[ADDRESS_BUF_LEN];

    d->scr.progress = jolt_gui_scr_loadingbar_create( TITLE_SEND );
    if( NULL == d->scr.progress ) {
        ESP_LOGE( TAG, "Failed to allocate loadingbar screen" );
        jolt_gui_scr_err_create( JOLT_GUI_ERR_OOM );
    }
    jolt_gui_scr_loadingbar_update( d->scr.progress, NULL, "Getting Frontier", 10 );

    /***********************************************
     * Get My Public Key, Private Key, and Address *
     ***********************************************/
    if( !{{cookiecutter.app_var_name}}_index_get_private_public_address( NULL, NULL, my_address, d->cfg.account_index ) ) {
        goto exit;
    }
    ESP_LOGI( TAG, "My Address: %s\n", my_address );

    /* TODO: Perform network action */
    jolt_gui_scr_set_event_cb( d->scr.progress, cleanup_complete_cb );

    return;

exit:
    cleanup_complete( NULL );
    return;
}

/**
 * @brief Create the amount-entry screen
 */
static void contact_cb( jolt_gui_obj_t *btn_sel, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) {
        d->contact_index = jolt_gui_scr_menu_get_btn_index( btn_sel );

        ESP_LOGD( TAG, "Creating Digit Entry Screen" );
        d->scr.entry = jolt_gui_scr_digit_entry_create(
                TITLE_SEND,
                CONFIG_JOLT_{{cookiecutter.app_var_name | upper}}_SEND_DIGITS,
                CONFIG_JOLT_{{cookiecutter.app_var_name | upper}}_SEND_DECIMALS );
        if( NULL == d->scr.entry ) {
            ESP_LOGE( TAG, "Failed to create digit entry screen" );
            return;
        }
        /* Set the first entry position to the one's place */
        jolt_gui_scr_digit_entry_set_pos(
                d->scr.entry, CONFIG_JOLT_{{cookiecutter.app_var_name | upper}}_SEND_DECIMALS );

        jolt_gui_scr_set_event_cb( d->scr.entry, processing_cb_1 );
    }
}

void {{cookiecutter.app_var_name}}_menu_send_contact( jolt_gui_obj_t *btn, jolt_gui_event_t event )
{
    if( jolt_gui_event.short_clicked == event ) {
        /* Create context */
        ESP_LOGD( TAG, "Allocating space for send context" );
        d = malloc( sizeof( send_obj_t ) );
        if( NULL == d ) {
            ESP_LOGE( TAG, "Could not allocate memory for send_obj_t" );
            return;
        }
        memset( d, 0, sizeof( send_obj_t ) );
        d->contact_index = -1;

        /* Read Config */
        d->cfg.root     = {{cookiecutter.app_var_name}}_get_json();  // never fails
        d->cfg.contacts = cJSON_Get( d->cfg.root, "contacts" );

        d->cfg.account_index = {{cookiecutter.app_var_name}}_index_get( d->cfg.root );

        if( NULL == d->cfg.contacts || 0 == cJSON_GetArraySize( d->cfg.contacts ) ) {
            d->scr.error = jolt_gui_scr_text_create( TITLE, "No Contacts" );
            jolt_gui_scr_set_event_cb( d->scr.error, cleanup_complete_cb );
            return;
        }

        ESP_LOGD( TAG, "Creating contacts menu" );
        d->scr.contacts = jolt_gui_scr_menu_create( TITLE );
        if( NULL == d->scr.contacts ) {
            ESP_LOGE( TAG, "Failed to create contacts menu" );
            cleanup_complete( NULL );
            return;
        }
        jolt_gui_scr_set_event_cb( d->scr.contacts, cleanup_complete_cb );
        jolt_gui_scr_set_active_param( d->scr.contacts, d );

        ESP_LOGD( TAG, "Iterating through saved contacts" );
        cJSON *contact = NULL;
        cJSON_ArrayForEach( contact, d->cfg.contacts )
        {
            cJSON *elem;
            elem = cJSON_Get( contact, "name" );
            ESP_LOGD( TAG, "Adding contact list element-name \"%s\"", cJSON_GetStringValue( elem ) );
            BREAK_IF_NULL( jolt_gui_scr_menu_add( d->scr.contacts, NULL, cJSON_GetStringValue( elem ), contact_cb ) );
        }
    }
}
