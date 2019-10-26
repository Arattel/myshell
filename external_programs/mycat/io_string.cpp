//
// Created by arattel on 07.10.19.
//
#include <string>
#include "io.h"


int read_file_to_string(std::string& file_path, std::string& file){
    const char * file_path_char = file_path.c_str();
    char *  file_buf;
    int file_read = read_file(file_path_char, &file_buf);
    if(file_read){ return file_read;}
    file = file_buf;
    free(file_buf);
    return 0;
}

int print_str(std::string& file){
    return print(file.c_str());
}

