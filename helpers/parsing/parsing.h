//
// Created by arattel on 21.10.19.
//

#ifndef MY_SHELL_PARSING_H
#define MY_SHELL_PARSING_H

#include <string>
#include <vector>


std::string get_next_word(std::string& input_line, std::string& cropped);
std::string get_next_word(std::string& input_line);

void between_delimiters(std::string& string, std::string delim, unsigned& start_ref, unsigned& end_ref);
void between_delimiters(std::string& string, std::string delim0, std::string delim1, unsigned& start_ref, unsigned& end_ref);


int get_command_line_args(std::string input_line, std::vector<std::string>& result);

#endif //MY_SHELL_PARSING_H
