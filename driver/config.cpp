#include "config.h"

#include <odbcinst.h>
#include <string.h>
#include "utils.h"
#include "log/log.h"
#include "win/version.h"

// ConnInfo::ConnInfo() { }

void getDSNinfo(ConnInfo * ci, bool overwrite) {

//        { auto rd = FUNCTION_MAYBE_W(SQLGetPrivateProfileString)                    \

#define GET_CONFIG(NAME, INI_NAME, DEFAULT)                             \
    if (ci->NAME[0] == '\0' || overwrite)                               \
        { auto rd = FUNCTION_MAYBE_W(SQLGetPrivateProfileString)        \
    (ci->dsn,                                                           \
        static_cast<LPCTSTR>(static_cast<const void *>(INI_NAME)),      \
        static_cast<LPCTSTR>(static_cast<const void *>(TEXT(DEFAULT))), \
        ci->NAME,                                                       \
        sizeof(ci->NAME),                                               \
        static_cast<LPCTSTR>(static_cast<const void *>(ODBC_INI))); \
        LOG("config: " << INI_NAME << " : " << STRING(NAME)); hex_print(log_stream, std::string(static_cast<const char*>(static_cast<const void *>(ci->NAME)), rd)); }

        //LOG("config: " << STRING(NAME) << " : " << static_cast<const char*>(static_cast<const void *>(ci->NAME))); }


/*
#define GET_CONFIG(NAME, INI_NAME, DEFAULT) if (ci->NAME[0] == '\0' || overwrite) { \
            auto rd = SQLGetPrivateProfileString(ci->dsn, INI_NAME, TEXT(DEFAULT), ci->NAME, sizeof(ci->NAME), ODBC_INI); \
            LOG("config: " << STRING(NAME)); hex_print(log_stream, std::string(static_cast<const char*>(static_cast<const void *>(ci->NAME)), rd)); \
        }
*/

    GET_CONFIG(desc, INI_KDESC, "");
    GET_CONFIG(url, INI_URL, "");
    GET_CONFIG(server, INI_SERVER, "");
    GET_CONFIG(database, INI_DATABASE, "");
    GET_CONFIG(username, INI_USERNAME, "");
    GET_CONFIG(port, INI_PORT, "");
    GET_CONFIG(onlyread, INI_READONLY, "");
    GET_CONFIG(password, INI_PASSWORD, "");
    GET_CONFIG(timeout, INI_TIMEOUT, "30");
    GET_CONFIG(sslmode, INI_SSLMODE, "");
    GET_CONFIG(stringmaxlength, INI_STRINGMAXLENGTH, "1048575");
    GET_CONFIG(trace, INI_TRACE, "");
    GET_CONFIG(tracefile, INI_TRACEFILE, LOG_DEFAULT_FILE);

#undef GET_CONFIG
}
