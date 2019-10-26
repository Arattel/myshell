//
// Created by arattel on 23.10.19.
//

#ifndef MY_SHELL_FILESYSTEM_H
#define MY_SHELL_FILESYSTEM_H

#include <vector>
#include <string>

int get_absolute_path(std::string& relative_path, std::string& current_directory, std::string& result);
std::string get_filename(std::string& path);
std::string get_dirname(std::string& path);
std::vector<std::string> list_files(std::string directory);
std::vector<std::string> filter_files(std::vector<std::string>& files_list, std::string wildcard);
#endif //MY_SHELL_FILESYSTEM_H
