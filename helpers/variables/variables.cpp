//
// Created by arattel on 23.10.19.
//

#include "variables.h"



void get_envp(char** buffer, std::set<std::string>& global){
    size_t len = global.size();
    buffer[len] = NULL;
    size_t counter = 0;
   for(auto elem:global){
       elem = elem + "=" + std::string(getenv(elem.c_str()));
       buffer[counter] = const_cast<char *>(elem.c_str());
       counter++;
   }
}

bool variable_exists(std::string& varname){
    return getenv(varname.c_str()) != nullptr;
}

void split_assignment(std::string& var, std::string& varname, std::string& value){
    unsigned position = var.find("=");
    varname = var.substr(0, position);
    value = var.substr(position + 1);
}

