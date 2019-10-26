//
// Created by arattel on 20.10.19.
//
#include "console_io.h"
#include <unistd.h>
#include <iostream>
#include <limits>



std::string get_current_path(){
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    return std::string(cwd);
}

void standard_shell_output(std::string& current_path){
    std::cout << current_path << " $";
}

std::string get_input(){
    std::string temp;
    std::getline(std::cin, temp);
    return temp;
}
