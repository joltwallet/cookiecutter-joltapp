#include "japp.h"
#include "jolt_lib.h"
#include "unity.h"

static const char MODULE_NAME[] = "[{{cookiecutter.app_name}}/cli]";

#define argcount( x ) ( sizeof( x ) / sizeof( const char * ) )

TEST_CASE( "cli example", MODULE_NAME )
{
    vault_set_unit_test( CONFIG_APP_COIN_PATH, CONFIG_APP_BIP32_KEY );

    JOLT_CLI_UNIT_TEST_CTX( 4096 )
    {
        const char *argv[] = {"about"};
        TEST_ASSERT_EQUAL_INT( JOLT_CLI_NON_BLOCKING, japp_main( argcount( argv ), argv ) );
        TEST_ASSERT_EQUAL_INT( 0, jolt_cli_get_return() );
        TEST_ASSERT_EQUAL_STRING( "", buf );
    }
}
