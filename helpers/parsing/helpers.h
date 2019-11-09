//
// Created by arattel on 21.10.19.
//

#ifndef MY_SHELL_HELPERS_H
#define MY_SHELL_HELPERS_H

#include <vector>
#include <string>


char ** strings_vector_to_char_arr(std::vector<std::string>& args);
bool substring_in_string(std::string string, std::string substring);
bool is_assignment(std::string& arg);
bool is_reference(std::string& arg);
bool is_number( std::string token );
std::vector<std::string> split(std::string mystring, std::string delimiter);
bool is_command_for_variable(std::string& value);
std::string trim_comment(std::string line);
#endif //MY_SHELL_HELPERS_H
