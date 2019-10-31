//
// Created by arattel on 31.10.19.
//

#include "split_into_groups.h"


void directories_first(std::vector<Entry>& input, std::vector<Entry>& first, std::vector<Entry>& second){
    for(auto& entry:input){
        if(entry.type == directory){
            first.push_back(entry);
        } else{
            second.push_back(entry);
        }
    }
}
void special_first(std::vector<Entry>& input, std::vector<Entry>& first, std::vector<Entry>& second){
    for(auto& entry:input){
        if(entry.type == file || entry.type == directory){
            second.push_back(entry);
        } else{
           first.push_back(entry);
        }
    }
}
void all_equal(std::vector<Entry>& input, std::vector<Entry>& first, std::vector<Entry>& second){
    first = input;
    second = {};
}

