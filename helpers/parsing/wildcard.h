//
// Created by arattel on 22.10.19.
//

#ifndef MY_SHELL_WILDCARD_H
#define MY_SHELL_WILDCARD_H

#include <vector>
#include <string>


bool is_wildcard(std::string string);
std::vector<std::string> find_files_given_wildcard(std::string current_path, std::string wildcard);
int get_files_by_wildcard(std::string wildcard, std::vector<std::string>& result);
#endif //MY_SHELL_WILDCARD_H
