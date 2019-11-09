//
// Created by arattel on 07.11.19.
//

#ifndef MYSHELL_EXECUTION_H
#define MYSHELL_EXECUTION_H
#include <vector>
#include <string>
#include <set>


void execute_command(std::vector<std::string>& args, std::set<std::string>& global, std::set<std::string>& local,
                     std::string& cur_path);
void execute_line(std::string& input, std::set<std::string>& global, std::set<std::string>& local,
                  std::string& cur_path);

std::string read(std::string& filename);
std::vector<std::string> get_lines(std::string& file_contents);

void execute_script(std::string filename,  std::set<std::string>& global, std::set<std::string>& local,
                    std::string& cur_path);

#endif //MYSHELL_EXECUTION_H
