//
// Created by arattel on 30.10.19.
//
#include "filesystem.h"
#include <boost/filesystem.hpp>
#include <iostream>
#include <boost/range/iterator_range.hpp>
#include "../../../helpers/filesystem/filesystem.h"

namespace fs = boost::filesystem;

void filter_nonexistent_files_vector(std::vector<std::string>& filenames){
    std::vector<std::string> existent_filenames;
    for(auto& entry:filenames){
        if(exists(entry)){
            existent_filenames.push_back(entry);
        } else{
            std::cerr << "Invalid path \"" << entry << "\" "<< std::endl;
        }
    }
    filenames = existent_filenames;
}

