//
// Created by arattel on 23.10.19.
//

#ifndef MY_SHELL_VARIABLES_H
#define MY_SHELL_VARIABLES_H

#include <set>
#include <string>

void get_envp(char** buffer, std::set<std::string>& global);
bool variable_exists(std::string& varname);
void split_assignment(std::string& var, std::string& varname, std::string& value);

#endif //MY_SHELL_VARIABLES_H
