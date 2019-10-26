//
// Created by arattel on 22.10.19.
//
#include <boost/regex.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>
#include "wildcard.h"
#include "helpers.h"
#include "../my_errno_values/my_errno.h"
#include "../filesystem/filesystem.h"


bool is_wildcard(std::string string){
    return substring_in_string(string, "*") || substring_in_string(string, "?") ||
    (substring_in_string(string, "[") && substring_in_string(string, "]"));
}

int get_files_by_wildcard(std::string wildcard, std::vector<std::string>& result){
    std::string absolute_path, dir_path, word_dir;
    try{
        dir_path = getenv("PATH");
        word_dir = get_dirname(wildcard);
        get_absolute_path(word_dir, dir_path, absolute_path);
        auto files = list_files(absolute_path);
        wildcard = get_filename(wildcard);
        for(int i = 0; i < files.size(); i++){
            files[i] = get_filename(files[i]);
        }
        files = filter_files(files, wildcard);
        if(files.empty()){
            return 1;
        } else{
            result = files;
            return 0;
        }
    } catch (boost::filesystem::filesystem_error& err){
        std::cerr << "Wrong path" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_PATH).c_str(), true);
        return 1;
    }


}