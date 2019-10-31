//
// Created by arattel on 26.10.19.
//
#include "config.h"
#include <iostream>
#include <regex>

std::map<char, SortOrder> sort_order_mapping = {
        {'U', unsorted},
        {'S', by_size},
        {'t', by_modification_time},
        {'X', by_extension},
        {'N', by_name}
};


int parse_config(int argc, char** agrv, ls_config& config){
    bool everything_is_file = false;
    std::vector<std::string> files;

    for(int i = 1; i < argc; i++){
        std::string current_arg = agrv[i];
        if(substring_in_string(current_arg, "-") and !everything_is_file){
            if(current_arg == "--"){
                everything_is_file = true;
            } else{
                if(current_arg[0] == '-'){
                    auto pos = current_arg.rfind("-");
                    current_arg = current_arg.substr(
                            pos + 1
                    );
                    if(current_arg.size() == 1){
                        if(process_one_character_argument(current_arg, config)){ return 1;}
                    } else if(current_arg.size() > 1){

                        if(process_long_argument(current_arg, config)){ return  1;}
                    } else{
                        std::cerr << "Invalid argument: too short" << std::endl;
                        return 1;
                    }
                } else{
                    files.emplace_back(current_arg);
                }


            }
        } else {
            files.push_back(current_arg);
        }
    }
    if(!files.empty()){
        config.filenames = files;
    } else{
        config.filenames = {"."};
    }

    return 0;
}

int process_one_character_argument(std::string& argument, ls_config& config){
    if(argument == "r"){
        config.reverse_order = true;
        return 0;
    } else if(argument == "R"){
        config.recursive = true;
        return 0;
    } else if(argument == "F"){
        config.show_types = true;
        return 0;
    } else if(argument == "l"){
        config.detailed = true;
        return 0;
    }
    else if(argument == "h"){
        config.show_help  = true;
    }else{
        std::cerr << "Invalid argument: -" << argument;
        return 1;
    }
}
int process_long_argument(std::string& argument, ls_config& config){
    std::regex regex("sort=([U|S|t|X|N][D|s]|[D|s]|[U|S|t|X|N])");
    if(argument == "help"){
        config.show_help = true;
    } else if(std::regex_match(argument, regex)){
        argument = argument.substr(5);
        process_sort_config(argument, config);
    } else{
        std::cerr << "Invalid argument" << std::endl;
        return 1;
    }
    return 0;
}
void process_sort_config(std::string& sort_conf_str, ls_config& config){
    for(auto& character:sort_conf_str){
        if(sort_order_mapping.find(character) != sort_order_mapping.end()){
            config.order = sort_order_mapping[character];
        } else{
            if(character == 'D'){
                config.directories_first = true;
            } else if(character == 's'){
                config.special_files_first = true;
            }
        }
    }
};

bool substring_in_string(std::string string, std::string substring){
    return string.find(substring) !=  std::string::npos;
}