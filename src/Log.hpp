#ifndef RL_LOG_HPP
#define RL_LOG_HPP

#if GAME_INTERNAL
#define LOG(TYPE, ...) _log(__FILE__, __FUNCTION__, __LINE__, TYPE, __VA_ARGS__)
#else
#define LOG(TYPE, ...)
#endif

global_variable int SESSION_TRACKER;

FILE* fileHandler;

enum GAME_LOG {
    GAME_LOG_DEBUG,
    GAME_LOG_INFO,
    GAME_LOG_WARNING,
    GAME_LOG_ERROR,
    GAME_LOG_CRITICAL
};

void
_log(char* path, char* function, int line, GAME_LOG type, char* vaArgs, ...);

#endif