//
// Created by arattel on 08.10.19.
//
#include "fitering.h"
#include <iostream>
#include <sstream>

std::string character_to_hex_string(char character){
    int character_code = (int) character;
    std::stringstream ss;
    ss << "\\x" <<  std::hex << character_code;
    return ss.str();
}


std::string filter_nonprintable_hex(std::string& unfiltered){
    std::string filtered_string = "";
    for(char character:unfiltered){
        if (!isspace((int) character) && !isprint((int) character)){
            filtered_string += character_to_hex_string(character);
        } else{
            filtered_string.push_back(character);
        }
    }
    return filtered_string;
}
