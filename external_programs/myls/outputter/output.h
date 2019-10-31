//
// Created by arattel on 31.10.19.
//

#ifndef MYLS_OUTPUT_H
#define MYLS_OUTPUT_H

#include "../filesystem_classes/Entry.h"

void print_detailed_file_information(Entry& file, std::string (*filename_formatter)(Entry&));
void print_file_information(Entry& file, std::string (*filename_formatter)(Entry&));
std::string get_time_string(Entry& file);
#endif //MYLS_OUTPUT_H
