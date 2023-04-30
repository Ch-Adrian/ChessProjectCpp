#include "pch.h"
#include "InitializationException.h"

InitializationException::InitializationException(const std::string msg)
	: std::exception() {
	this->message = "Initialization exception: " + msg;
}

const char* InitializationException::what() {
	return this->message.c_str();
}
