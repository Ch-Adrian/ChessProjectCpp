#pragma once

#include "SdlIncludes.h"

class NullPointerException : public std::exception
{
private:
    std::string message;
public:

    NullPointerException(const std::string msg);
    const char* what() const;
};

