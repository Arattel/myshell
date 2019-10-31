//
// Created by arattel on 31.10.19.
//

#include <map>
#include "filename_formats.h"
#include "../config/config.h"

std::map<file_type, char> type_chars = {
        {executable, '*'},
        {symlink_type, '@'},
        {file, ' '},
        {named_pipe, '|'},
        {socket, '='},
        {other, '?'}
};


std::string just_filename(Entry& entry){
    return entry.name;
}

std::string special_files_marked(Entry& entry){
    return entry.name + type_chars[entry.type];
}