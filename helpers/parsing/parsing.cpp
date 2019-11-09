//
// Created by arattel on 21.10.19.
//
#include "parsing.h"
#include <boost/algorithm/string.hpp>
#include <iostream>
#include "wildcard.h"
#include "helpers.h"
#include "../my_errno_values/my_errno.h"
#include "../variables/variables.h"




std::string get_next_word(std::string& input_line, std::string& cropped){
    unsigned start, end;
    std::string first_word;
    if(input_line.find(" ") != std::string::npos){
        between_delimiters(input_line, "", " ", start, end);

        first_word = input_line.substr(start, end - start);
        if(first_word.find("\"") != std::string::npos){
            between_delimiters(input_line, "\"", start, end);
            first_word = input_line.substr(0, start) + input_line.substr(start + 1, end - start - 1);
        }
        cropped = input_line.substr(end + 1, input_line.size() - end);
    }else{
       first_word = input_line;
        if(first_word.find("\"") != std::string::npos){
            between_delimiters(input_line, "\"", start, end);
            first_word = input_line.substr(0, start) + input_line.substr(start + 1, end - start - 1);
        }
        cropped = "";
    }
    return first_word;

}

std::string get_next_word(std::string& input_line){
    unsigned start, end;
    between_delimiters(input_line, "", " ", start, end);

    std::string first_word = input_line.substr(start, end - start);
    if(first_word.find("\"") != std::string::npos){
        between_delimiters(input_line, "\"", start, end);
        first_word = input_line.substr(0, start) + input_line.substr(start + 1, end - start - 1);

    }
    return first_word;

}

void between_delimiters(std::string& string, std::string delim, unsigned& start_ref, unsigned& end_ref){
    unsigned start, end, after_start;

    start = string.find(delim);
    after_start = start + 1;
    end = string.find_first_of(delim, after_start);

    start_ref  = start;
    end_ref = end;
}

void between_delimiters(std::string& string, std::string delim0, std::string delim1, unsigned& start_ref, unsigned& end_ref){
    unsigned start = string.find(delim0);
    unsigned after_start = start + delim0.length();
    unsigned end = string.find(delim1);
    start_ref  = start;
    end_ref = end;
}


int get_command_line_args(std::string input_line, std::vector<std::string>& result){
    std::vector<std::string> args;
    while (input_line.size() != 0){
        std::string word  = get_next_word(input_line, input_line);
        if(is_wildcard(word)){
            std::vector<std::string> files;
            int result = get_files_by_wildcard(word, files);
            if(!result){
                args.insert(args.end(), files.begin(), files.end());
            } else{
                std::cerr << "No files matching given wildcard" << std::endl;
                setenv("ERRNO", std::to_string(ERRNO_WRONG_WILDCARD).c_str(), true);
                return 1;
            }

        }
        else if(is_reference(word)){
            std::string varname = word.substr(1);
            if(variable_exists(varname)){
                word = getenv(varname.c_str());
                args.push_back(word);
            } else{
                std::cerr << "Variable " << varname << " doesn't exist" << std::endl;
                setenv("ERRNO", std::to_string(ERRNO_VARIABLE_NONEXISTENT).c_str(), true);
                return 1;
            }
        }else
            {
            args.push_back(word);
        }
    }
    result = args;
    setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    return 0;
}




