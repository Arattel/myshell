//
// Created by arattel on 07.11.19.
//

#include <fcntl.h>
#include "redirection.h"
#include "../parsing/helpers.h"
#include "../parsing/parsing.h"
#include "unistd.h"
#include <iostream>
#include <boost/regex.hpp>
#include <boost/algorithm/string.hpp>

std::vector<std::string> redirect_output(std::vector<std::string>& args){
    std::string line;
    for (const auto &piece : args) line += piece + " ";
    boost::regex expr{"(\\d*)(\\s*)(>|<)(\\s*)(\\S+)"};
    std::vector<std::string> redirections;
    boost::sregex_iterator it{ begin(line), end(line), expr }, itEnd;
    for (boost::sregex_iterator it = boost::sregex_iterator(line.begin(), line.end(), expr);
         it != boost::sregex_iterator(); it++) {
        boost::smatch match;
        match = *it;
        redirections.push_back(match.str(0));
    }
    line = boost::regex_replace(line, expr, "");
    get_command_line_args(line, args);
    return redirections;
}