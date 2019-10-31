//
// Created by arattel on 31.10.19.
//

#ifndef MYLS_SORTERS_H
#define MYLS_SORTERS_H

#include <vector>
#include "../filesystem_classes/Entry.h"

void not_sort(std::vector<Entry>& input);
void sort_by_size(std::vector<Entry>& input);
void sort_by_modification_time(std::vector<Entry>& input);
void sort_by_extension(std::vector<Entry>& input);
void sort_by_name(std::vector<Entry>& input);


std::string get_extension(std::string path);

#endif //MYLS_SORTERS_H
