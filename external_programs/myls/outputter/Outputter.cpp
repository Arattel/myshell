//
// Created by arattel on 31.10.19.
//

#include <map>
#include <iostream>
#include "Outputter.h"
#include "split_into_groups.h"
#include "sorters.h"
#include "filename_formats.h"
#include "output.h"

std::map<SortOrder, void (*)(std::vector<Entry>&)> sort_order_to_sorter = {
        {unsorted, not_sort},
        {by_size, sort_by_size},
        {by_modification_time, sort_by_modification_time},
        {by_extension, sort_by_extension},
        {by_name, sort_by_name}
};



Outputter::Outputter(ls_config& config){
    sorter  = sort_order_to_sorter[config.order];
    if(config.special_files_first){
        splitter = special_first;
    } else if(config.directories_first){
        splitter = directories_first;
    } else{
        splitter = all_equal;
    }

    if(config.detailed){
        printer = print_detailed_file_information;
    } else{
        printer = print_file_information;
    }
    if(config.show_types){
        filename_formatter = special_files_marked;
    } else{
        filename_formatter = just_filename;
    }
    reverse_order = config.reverse_order;
}

void Outputter::output(std::vector<Entry>& entries){
    std::vector<Entry> first;
    std::vector<Entry> second;
    splitter(entries, first, second);
    sorter(first);
    sorter(second);
    if(reverse_order){
        std::reverse(first.begin(), first.end());
        std::reverse(second.begin(), second.end());
    }
    first.insert(first.end(), second.begin(), second.end());
    for(auto& entry:first){
        if(entry.type == directory){
            this->output_directory(entry);
        } else{
            printer(entry, filename_formatter);
        }
    }
}


void Outputter::output_directory(Entry& dirent){
    std::cout << dirent.name << ":" << std::endl;
    this->output(dirent.children);
    std::cout << std::endl;
}