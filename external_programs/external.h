//
// Created by arattel on 23.10.19.
//

#ifndef MY_SHELL_EXTERNAL_H
#define MY_SHELL_EXTERNAL_H

#include <string>
#include <vector>
#include <set>

extern std::string PATH_TO_EXTERNALS;

bool is_local_external(std::string& path);
std::string path_to_local_external(std::string& path);
void run_external(std::string& path,  std::vector<std::string>& args, std::set<std::string>& global);
bool is_global_external(std::string& path);
std::string path_to_global_external(std::string& path);


#endif //MY_SHELL_EXTERNAL_H
