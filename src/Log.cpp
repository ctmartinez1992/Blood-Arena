#include "main.hpp"

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

internal_function char*
GetFilenameFromPath(char* path) {
	char* filename = path;

    for(char* scan = path; *scan; ++scan) {
        if(*scan == '\\') {
            filename = scan++;
        }
    }

    filename++;

    return(filename);
}

internal_function char*
GetTypeOfLog(GAME_LOG type) {
    char* typeString = 0;

    switch(type) {
        case GAME_LOG_DEBUG:		typeString = "DEBUG\0";		break;
        case GAME_LOG_INFO:			typeString = "INFO\0";		break;
        case GAME_LOG_WARNING:		typeString = "WARNING\0";	break;
        case GAME_LOG_ERROR:		typeString = "ERROR\0";		break;
        case GAME_LOG_CRITICAL:		typeString = "CRITICAL\0";	break;
        default:					typeString = "DEFAULT\0";	break;
    }

    return(typeString);
}

void _log(char* path, char* function, int line, GAME_LOG type, char* vaArgs, ...) {
    va_list list;

    fopen_s(&fileHandler, "log.txt", SESSION_TRACKER ? "a+" : "w");

    char* typeOfLog = GetTypeOfLog(type);

	fprintf(fileHandler, "[%s][%s - %s - %d] : ", typeOfLog, GetFilenameFromPath(path) , function, line);

    va_start(list, vaArgs);
 
    for(char* arg = vaArgs; *arg; ++arg) {
        if(*arg != '%') {
            fputc(*arg, fileHandler);
        }
        else {
            switch(*++arg) {
            
                //char
                case 's':
                {
                    char* argValueCharPointer = va_arg(list, char*);
                    fprintf(fileHandler, "%s", argValueCharPointer);
                } continue;
 
                //integer
                case 'd':
                {
                    int argValueInteger = va_arg(list, int);
                    fprintf(fileHandler, "%d", argValueInteger);  
                } continue;
 
                default:
                {
                    fputc(*arg, fileHandler);
                } break;
            }
        }
    }

    va_end(list);

    fputc('\n', fileHandler);

    SESSION_TRACKER++;

    fclose(fileHandler);
}

#define GAME_LOG_H
#endif