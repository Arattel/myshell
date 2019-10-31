//
// Created by arattel on 31.10.19.
//

#include "output.h"
#include <iostream>
#include <ctime>

void print_detailed_file_information(Entry& file, std::string (*filename_formatter)(Entry&)){
    std::string time = get_time_string(file);
    printf("%s  %zu  %s\n",  time.c_str(), file.size, filename_formatter(file).c_str());
}

void print_file_information(Entry& file, std::string (*filename_formatter)(Entry&)){
    std::cout << filename_formatter(file) << std::endl;
}


std::string get_time_string(Entry& file){
    char buffer [80];
    struct tm * timeinfo;
    timeinfo = localtime (&file.last_modified.tv_sec);
    strftime (buffer, 80, "%F %T", timeinfo);
    return std::string(buffer);
}
