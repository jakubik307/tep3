#pragma once
#include "Tree.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

void runInterface();

// Helper methods
std::string toLowercase(std::string& input);
std::string strip(std::string& input);
std::string removeNonOperators(const std::string& input, bool& isCorrect);
std::string fixDotsInNumbers(const std::string& input);
