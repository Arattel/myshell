//
// Created by arattel on 31.10.19.
//

#ifndef MYLS_FILENAME_FORMATS_H
#define MYLS_FILENAME_FORMATS_H

#include <string>
#include "../filesystem_classes/Entry.h"

std::string just_filename(Entry& entry);
std::string special_files_marked(Entry& entry);
#endif //MYLS_FILENAME_FORMATS_H
