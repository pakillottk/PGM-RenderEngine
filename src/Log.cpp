#include "Log.h"

void Log::print(const char* message, bool newLine)
{
    fprintf(stdout, "%s ", message);
    if(newLine)
    {
        fprintf(stdout, "%s", "\n");
    }
}

void Log::print(bool oneLineEach, const std::list<const char*>& args)
{
    for(const char* m : args)
    {
        print(m, oneLineEach);
    }
    print("\n");
}

void Log::print(const std::list<const char*>& args)
{
    print(false, args);
}    