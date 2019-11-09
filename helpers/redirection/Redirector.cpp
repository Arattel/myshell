//
// Created by arattel on 07.11.19.
//

#include "Redirector.h"
#include <boost/algorithm/string/trim.hpp>
#include <fcntl.h>
#include <iostream>
#include "../filesystem/filesystem.h"
#include "../parsing/helpers.h"
#include "../parsing/parsing.h"


std::vector<int> get_redirection(std::string& redirection){
    std::string from, to;
    unsigned split_index;
    int from_fd, to_fd;

    if(substring_in_string(redirection, ">")){
        split_index = redirection.find_last_of(">");
        from = redirection.substr(0, split_index);
        to = redirection.substr(split_index + 1, redirection.size() - split_index - 1);
        from = boost::trim_copy(from);
        to = boost::trim_copy(to);
        if(from.empty()){
            from_fd = STDOUT_FILENO;
        } else{
            from_fd = std::stoi(from);
        }
        if(to[0] == '&'){
            to = to.substr(1);
            to_fd = std::stoi(to);
        } else{
            std::string path = getenv("PATH");
            path += "/" + to;
            to_fd = open(path.c_str(), O_RDWR|O_CREAT, 0600);
        }
    } else{
        split_index = redirection.find_last_of("<");
        from = redirection.substr(split_index + 1, redirection.size() - split_index - 1);
        from = boost::trim_copy(from);
        std::string path = getenv("PATH");
        path += "/" + from;
        to_fd = open(path.c_str(), O_RDWR|O_CREAT, 0600);
        from_fd = STDIN_FILENO;
    }
    return std::vector<int>({from_fd, to_fd, dup(from_fd)});
}


Redirector::Redirector(std::vector<std::string>& redirections){
    for(auto& entry:redirections){
        from_to.push_back(get_redirection(entry));
    }
}

void Redirector::redirect() {
    for(auto& entry:from_to){
        dup2(entry[1], entry[0]);
    }
}

void Redirector::recover() {
    for(auto& entry:from_to){
        close(entry[1]);
        dup2(entry[2], entry[0]);
        close(entry[2]);
    }
}

std::vector<int> Redirector::get_redirected(){
    std::vector<int> descriptors;
    for(auto& entry:from_to){
        descriptors.push_back(entry[0]);
    }
    return descriptors;
}