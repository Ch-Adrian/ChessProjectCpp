#include "pch.h"
#include "InitializationException.h"

InitializationException::InitializationException(const std::string msg)
	: std::exception(msg.c_str()) {
	this->message = "Initialization exception: " + msg;
}

const char* InitializationException::what() const {
	return this->message.c_str();
}