#include "pch.h"
#include "NullPointerException.h"


NullPointerException::NullPointerException(const std::string msg)
	: std::exception() {
	this->message = "NullPointerException: " + msg;
}

const char* NullPointerException::what() {
	return this->message.c_str();
}
