//
// Created by arattel on 20.10.19.
//

#ifndef MY_SHELL_CONSOLE_IO_H
#define MY_SHELL_CONSOLE_IO_H
#include <string>

std::string get_current_path();
void standard_shell_output(std::string& current_path);
std::string get_input();

#endif //MY_SHELL_CONSOLE_IO_H
