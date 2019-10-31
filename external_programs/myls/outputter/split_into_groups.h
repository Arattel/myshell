//
// Created by arattel on 31.10.19.
//

#ifndef MYLS_SPLIT_INTO_GROUPS_H
#define MYLS_SPLIT_INTO_GROUPS_H

#include <vector>
#include "../filesystem_classes/Entry.h"

void directories_first(std::vector<Entry>& input, std::vector<Entry>& first, std::vector<Entry>& second);
void special_first(std::vector<Entry>& input, std::vector<Entry>& first, std::vector<Entry>& second);
void all_equal(std::vector<Entry>& input, std::vector<Entry>& first, std::vector<Entry>& second);
#endif //MYLS_SPLIT_INTO_GROUPS_H
