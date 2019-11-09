//
// Created by arattel on 08.11.19.
//

#ifndef MYSHELL_PIPE_H
#define MYSHELL_PIPE_H

#include <string>
#include <set>
#include <vector>

void execute_pipe(std::string& input_line, std::set<std::string>& global,  std::set<std::string>& local,
                  std::string& cur_path);

void piped_execution(std::vector<std::vector<std::string>>& all_piped_commands, std::set<std::string>& global,
                     std::set<std::string>& local, std::string& cur_path, int saved_stdin, int saved_stdout,
                     int saved_stderr);

#endif //MYSHELL_PIPE_H
