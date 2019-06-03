//#define LOG_LOCAL_LEVEL ESP_LOG_DEBUG

#include "jolt_lib.h"
#include "cmds.h"
#include "{{cookiecutter.app_var_name}}_helpers.h"

static const char TAG[] = "{{cookiecutter.app_var_name}}_cmd_address";
(void) TAG;

static uint32_t lower, upper;

void success_cb( void *param ) {
    for(uint32_t index=lower; index<=upper; index++ ){
        char address[ADDRESS_BUF_LEN] = { 0 };
        {{cookiecutter.app_var_name}}_index_get_address(address, index);
        printf("%d: %s\n", index, address);
    }

    jolt_cli_return(0);
}

void failure_cb( void *param ) {
    jolt_cli_return(-1);
}

int {{cookiecutter.app_var_name}}_cmd_address(int argc, char ** argv) {
    /* Argument Verification */
    if( !console_check_range_argc(argc, 1, 3) ){
        return 1;
    }

    /* Convert arguments to ints.
     * Note: atoi returns 0 if provided argument cannot be converted to integer. */
    if( 1 == argc ){
        /* Print only currently selected address */
        lower = {{cookiecutter.app_var_name}}_index_get( NULL );
        upper = lower;
    }
    else{
        /* Print range of addresses */
        lower = atoi( argv[1] );
        if( 3 == argc ){
            upper = atoi(argv[2]);
        }
        else {
            upper = lower;
        }
    }

    vault_refresh( failure_cb, success_cb, NULL);

    return JOLT_CLI_NON_BLOCKING;
}
