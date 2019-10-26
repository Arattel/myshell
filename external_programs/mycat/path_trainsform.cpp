//
// Created by arattel on 08.10.19.
//
#include "path_transform.h"
#include <iostream>
#include <boost/filesystem.hpp>

int get_absolute_path(std::string& relative_path, std::string& result){
    boost::filesystem::path relative(relative_path);
    try {
        boost::filesystem::path full_path(boost::filesystem::current_path());
        result = boost::filesystem::canonical(relative, full_path).string();
        return 0;
    } catch (std::exception& e){
        return 1;
    }


}