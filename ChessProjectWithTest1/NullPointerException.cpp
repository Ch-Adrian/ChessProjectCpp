#include "pch.h"
#include "NullPointerException.h"


NullPointerException::NullPointerException(const std::string msg)
	: std::exception(msg.c_str()) {
	this->message = "NullPointerException: " + msg;
}

const char* NullPointerException::what() const {
	return this->message.c_str();
}