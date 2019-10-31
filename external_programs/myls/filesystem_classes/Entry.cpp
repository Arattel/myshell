//
// Created by arattel on 30.10.19.
//

#include "Entry.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <iostream>
#include "../config/config.h"
#include <dirent.h>



Entry::Entry(std::string filename, ls_config& cfg, bool is_subdir) {
    struct  stat file_data;
    lstat(filename.c_str(), &file_data);
    name = filename;
    get_file_type(file_data, type, filename);
    if(type != directory){
        name = basename(name.c_str());
    }
    last_modified = file_data.st_mtim;
    size = file_data.st_size;
    if(type == directory && (!is_subdir || cfg.recursive)){
        list_files_in_directory(name, children, cfg);
    }
}

int can_exec(std::string file){
    return !access(file.c_str(), X_OK);
}

int exists(std::string path)
{
    if (access(path.c_str(), F_OK) == -1)
        return 0;
    return 1;
}

void list_files_in_directory(std::string dir_name, std::vector<Entry>& files, ls_config& conf){
    DIR *dpdf;
    struct dirent *epdf;
    dpdf = opendir(dir_name.c_str());
    if (dpdf != NULL) {
        while (epdf = readdir(dpdf)) {
            auto name = std::string(epdf->d_name);
            if(name != "." && name != ".."){
                files.push_back(Entry(combine(dir_name, name), conf, true));
            }
        }
    }
}

void walk_files(std::vector<Entry>& entries, ls_config& cfg){
    for(auto& filename:cfg.filenames){
        auto entry  = Entry(filename, cfg, false);
        if(entry.type != directory){
            entries.push_back(entry);
        } else{
            entries.push_back(entry);
        }
    }
}


void get_file_type(struct stat& file_data, file_type& type, std::string& filename){
   auto mode = file_data.st_mode;
   if(S_ISDIR(mode)){
       type = directory;
   } else if(S_ISREG(mode)){
       if(can_exec(filename)){
           type = executable;
       } else{
           type = file;
       }
   } else if(S_ISFIFO(mode)){
       type = named_pipe;
   } else if(S_ISLNK(mode)){
       type = symlink_type;
   } else if(S_ISSOCK(mode)){
       type = socket;
   } else{
       type = other;
   }
}

std::string combine(std::string dir, std::string file){
    if(dir[dir.size()  - 1] == '/'){
        return dir + file;
    } else{
        return dir + "/" + file;
    }
}