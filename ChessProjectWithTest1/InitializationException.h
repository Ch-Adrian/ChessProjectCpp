#include "pch.h"
#pragma once
#include "SdlIncludes.h"

class InitializationException : public std::exception
{
private:
    std::string message;
public:

    InitializationException(const std::string msg);
    const char* what() const;
};

