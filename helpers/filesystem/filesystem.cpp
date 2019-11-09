//
// Created by arattel on 23.10.19.
//
#include "filesystem.h"
#include "../parsing/helpers.h"
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range_core.hpp>
#include <fnmatch.h>
#include <cstdlib>
#include <cstdio>

int get_absolute_path(std::string& relative_path, std::string& current_directory, std::string& result){
    boost::filesystem::path relative(relative_path);
    try {
        boost::filesystem::path full_path(current_directory);
        result = boost::filesystem::canonical(relative, full_path).string() + "/";
        return 0;
    } catch (std::exception& e){
        return 1;
    }
}

std::string get_filename(std::string& path){
    std::string sp = "/";
    if(substring_in_string(path, sp)){
        unsigned index = path.find_last_of(sp);
        return path.substr(index + 1);
    }
    return path;
}

std::string get_dirname(std::string& path){
    boost::filesystem::path pth(path);
    pth.remove_filename();
    return pth.string();
}

std::vector<std::string> list_files(std::string directory){
    std::vector<std::string> files;
    for(auto& entry : boost::make_iterator_range(boost::filesystem::directory_iterator(directory), {})){
        files.emplace_back(entry.path().string());
    }
    return files;
}

std::vector<std::string> filter_files(std::vector<std::string>& files_list, std::string wildcard){
    std::vector<std::string> filtered;
    for(auto& file:files_list){
        if(!fnmatch(wildcard.c_str(), file.c_str(), 0)){
            filtered.emplace_back(file);
        }
    }
    return filtered;
}

std::string read_file_into_string(int fd){
    char *string = (char *) malloc(4096);
    read(fd, string, 4096);
    return std::string(string);
}