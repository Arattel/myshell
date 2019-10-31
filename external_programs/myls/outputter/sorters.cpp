//
// Created by arattel on 31.10.19.
//

#include "sorters.h"
#include <string>

struct less_than_size
{
    inline bool operator() (const Entry& struct1, const Entry& struct2)
    {
        return (struct1.size < struct2.size);
    }
};
struct less_than_time
{
    inline bool operator() (const Entry& struct1, const Entry& struct2)
    {
        return (struct1.last_modified.tv_sec < struct2.last_modified.tv_sec);
    }
};
struct less_than_extension
{
    inline bool operator() (const Entry& struct1, const Entry& struct2)
    {
        std::string ext1 = get_extension(struct1.name);
        std::string ext2 = get_extension(struct2.name);
        return (ext1 < ext2);
    }
};
struct less_than_name
{
    inline bool operator() (const Entry& struct1, const Entry& struct2)
    {
        return (struct1.name  < struct2.name);
    }
};




void not_sort(std::vector<Entry>& input){}
void sort_by_size(std::vector<Entry>& input){
    std::sort(input.begin(), input.end(), less_than_size());
}
void sort_by_modification_time(std::vector<Entry>& input){
    std::sort(input.begin(), input.end(), less_than_time());

}
void sort_by_extension(std::vector<Entry>& input){
    std::sort(input.begin(), input.end(), less_than_extension());

}
void sort_by_name(std::vector<Entry>& input){
    std::sort(input.begin(), input.end(), less_than_name());
}

std::string get_extension(std::string path){
    if(path.find_last_of(".") == std::string::npos){
        return "";
    } else{
        return  path.substr(path.find_last_of("."));
    }
}