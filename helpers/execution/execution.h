//
// Created by arattel on 07.11.19.
//

#ifndef MYSHELL_EXECUTION_H
#define MYSHELL_EXECUTION_H
#include <vector>
#include <string>
#include <set>


void execute_command(std::vector<std::string>& args, std::set<std::string>& global, std::string& cur_path);
#endif //MYSHELL_EXECUTION_H
