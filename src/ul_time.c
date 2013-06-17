#include <stdint.h>
#include <sys/time.h>
#include "ul_time.h"

// converts timeval structure to 64-bit unsigned
#define TV_TO_64(tv) ( (uint64_t)tv.tv_sec * 1000000ULL + (uint64_t)tv.tv_usec )

inline void delay_us( uint64_t del ) {
    struct timeval tv;
    gettimeofday(&tv, NULL);  // get starting time
    uint64_t t_cmp = TV_TO_64(tv) + del;
    uint64_t t_cur;
    do {
        gettimeofday(&tv, NULL);  // get current time
        t_cur = TV_TO_64(tv);
    } while (t_cur < t_cmp);
}

// delay in microseconds
static int ul_time_delay_us(lua_State *L) {
    if (lua_isnumber(L, 1)) { // 1st parameter is number ?
        delay_us( lua_tointeger(L, 1) );
    }
    return 0;
}

// delay in milliseconds
static int ul_time_delay_ms(lua_State *L) {
    if (lua_isnumber(L, 1)) { // 1st parameter is number ?
        delay_us( (uint64_t)lua_tointeger(L, 1) * 1000 );
    }
    return 0;
}

// delay in seconds
static int ul_time_delay_s(lua_State *L) {
    if (lua_isnumber(L, 1)) { // 1st parameter is number ?
        delay_us( (uint64_t)lua_tointeger(L, 1) * 1000000 );
    }
    return 0;
}


// returns current seconds and microseconds
static int ul_timeofday(lua_State *L) {
    struct timeval tv;             // seconds/useconds structure
    gettimeofday(&tv, NULL);       // get current time
    lua_pushinteger(L, (lua_Integer)tv.tv_sec);  // 1st result
    lua_pushinteger(L, (lua_Integer)tv.tv_usec); // second result
    return 2;                      // number of results
}

static const luaL_reg lib_ul_time[] = {
    {"delay_us",  ul_time_delay_us},
    {"delay_ms",  ul_time_delay_ms},
    {"delay_s",   ul_time_delay_s},
    {"timeofday", ul_timeofday},
    {NULL, NULL}
};

LUALIB_API int luaopen_ul_time(lua_State *L) {
    luaL_register(L, "ul_time", lib_ul_time);

    lua_getglobal(L, "os");
    if (lua_istable(L, -1)) {

        lua_pushstring(L, "delay_us");
        lua_pushcfunction(L, ul_time_delay_us);
        lua_settable(L, -3);

        lua_pushstring(L, "delay_ms");
        lua_pushcfunction(L, ul_time_delay_ms);
        lua_settable(L, -3);

        lua_pushstring(L, "delay_s");
        lua_pushcfunction(L, ul_time_delay_s);
        lua_settable(L, -3);

        lua_pushstring(L, "timeofday");
        lua_pushcfunction(L, ul_timeofday);
        lua_settable(L, -3);

    }
    lua_pop(L, 1);
    return 1;
}

