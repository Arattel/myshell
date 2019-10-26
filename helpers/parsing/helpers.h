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

#endif //MY_SHELL_HELPERS_H
