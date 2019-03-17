#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <list>

namespace Log
{
    void print(const char* message, bool newLine = true);
    void print(bool oneLineEach, const std::list<const char*>& args);
    void print(const std::list<const char*>& args);
} // Log