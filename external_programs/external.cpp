//
// Created by arattel on 23.10.19.
//
#include "external.h"
#include "../helpers/filesystem/filesystem.h"
#include "../helpers/parsing/helpers.h"
#include "../helpers/variables/variables.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <iostream>
#include <set>


std::string PATH_TO_EXTERNALS = "external_programs/";
bool is_local_external(std::string& path){
    std::string default_path = getenv("DEFAULT_PATH");
    default_path =  default_path + "/" + PATH_TO_EXTERNALS;
    auto contents = list_files(default_path);
    bool is_external_local = false;
    for(int i = 0; i < contents.size(); i++){
        auto cnt = contents[i];
        cnt = get_filename(cnt);
        if(!substring_in_string(cnt, ".")){
            if(cnt == path){
                is_external_local = true;
            }
        }
    }
    return is_external_local;
}

bool is_global_external(std::string& path){
    std::string abspath;
    std::string current_path = getenv("PATH");
    int status = get_absolute_path(path, current_path, abspath);
    return status == 0;
}
std::string path_to_local_external(std::string& path){
    std::string default_path = getenv("DEFAULT_PATH");
    default_path = default_path + "/" + PATH_TO_EXTERNALS  + path + "/" + path;
    return default_path;
}
std::string path_to_global_external(std::string& path){
    std::string pth;
    std::string current_path = getenv("PATH");
    get_absolute_path(path, current_path, pth);
    return pth.substr(0, pth.size() - 1);
}
void run_external(std::string& path,  std::vector<std::string>& args, std::set<std::string>& global){
    pid_t parent = getpid();
    char *envp[global.size() + 1];
    get_envp(envp, global);


    size_t length_of_args_buffer = args.size();
    char *args_buffer[length_of_args_buffer];
    args_buffer[length_of_args_buffer] = NULL;
    size_t counter = 0;
    for(auto& elem:args){
        args_buffer[counter] = const_cast<char *>(elem.c_str());
        counter++;
    }



    pid_t pid = fork();
    if (pid == -1)
    {
        std::cerr << "Failed to fork()" << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        int status;
        waitpid(pid, &status, 0);
    }else
    {
        // We are the child
        execve(path.c_str(), args_buffer, envp);
        std::cerr << "Parent: Failed to execute " << path << " \n\tCode: " << errno << std::endl;
        exit(EXIT_FAILURE);   // exec never returns
    }
}

