//
// Created by arattel on 21.10.19.
//
#include "helpers.h"
#include <boost/filesystem.hpp>
#include <libgen.h>
#include <boost/range/iterator_range_core.hpp>
#include <boost/regex.hpp>
#include <fnmatch.h>
#include <regex>
#include <boost/algorithm/string.hpp>


char ** strings_vector_to_char_arr(std::vector<std::string>& args){
    std::vector<char*> cstrings;
    cstrings.reserve(args.size());

    for(size_t i = 0; i < args.size(); ++i)
        cstrings.push_back(const_cast<char*>(args[i].c_str()));
    return cstrings.data();
}
bool substring_in_string(std::string string, std::string substring){
    return string.find(substring) !=  std::string::npos;
}

bool is_assignment(std::string& arg){
    return substring_in_string(arg, "=");
}

bool is_reference(std::string& arg){
    return substring_in_string(arg, "$") && arg[arg.find_first_of("$") + 1] != '(';
}

bool is_number( std::string token )
{
    return std::regex_match( token, std::regex( ( "((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?" ) ) );
}


std::vector<std::string> split(std::string mystring, std::string delimiter)
{
    std::vector<std::string> subStringList;
    std::string token;
    while (true)
    {
        size_t findfirst = mystring.find_first_of(delimiter);
        if (findfirst == std::string::npos) //find_first_of returns npos if it couldn't find the delimiter anymore
        {
            subStringList.push_back(mystring); //push back the final piece of mystring
            return subStringList;
        }
        token = mystring.substr(0, mystring.find_first_of(delimiter));
        mystring = mystring.substr(mystring.find_first_of(delimiter) + 1);
        subStringList.push_back(token);
    }

    return subStringList;
}

bool is_command_for_variable(std::string& value){
   std::regex reg{"\\$\\(.*\\)"};
    return  std::regex_match(value, reg);
}

std::string trim_comment(std::string line){
    if(substring_in_string(line, "#")){
        unsigned comment_index = line.find_first_of("#");
        return line.substr(0, comment_index);
    } else{
        return line;
    }
}