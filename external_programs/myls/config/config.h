//
// Created by arattel on 26.10.19.
//

#ifndef MYLS_CONFIG_H
#define MYLS_CONFIG_H

#include <vector>
#include <string>
enum SortOrder{unsorted, by_size, by_modification_time, by_extension, by_name};

struct ls_config{
    SortOrder order;
    bool reverse_order;
    bool recursive;
    bool detailed;
    bool show_types;
    bool show_help;
    bool special_files_first;
    bool directories_first;
    std::vector<std::string> filenames;
    ls_config() {
        order = by_name;
        reverse_order = false;
        recursive = false;
        detailed  = false;
        show_types = false;
        show_help = false;
        special_files_first = false;
        directories_first = false;
    }
};



int parse_config(int argc, char** agrv, ls_config& config);
int process_argument(std::string& argument, ls_config& config);
int process_one_character_argument(std::string& argument, ls_config& config);
int process_long_argument(std::string& argument, ls_config& config);
void process_sort_config(std::string& sort_conf_str, ls_config& config);
bool substring_in_string(std::string string, std::string substring);
#endif //MYLS_CONFIG_H
