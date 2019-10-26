//
// Created by arattel on 21.10.19.
//
#include "helpers.h"
#include <boost/filesystem.hpp>
#include <libgen.h>
#include <boost/range/iterator_range_core.hpp>
#include <boost/regex.hpp>
#include <fnmatch.h>


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
    return substring_in_string(arg, "$");
}

