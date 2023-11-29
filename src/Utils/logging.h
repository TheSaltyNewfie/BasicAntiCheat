#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "logging.tpp"

template <typename... Args>
void print(const std::string& fmt, Args... args);