//
// Created by arattel on 31.10.19.
//

#ifndef MYLS_OUTPUTTER_H
#define MYLS_OUTPUTTER_H

#include "../config/config.h"
#include "../filesystem_classes/Entry.h"

enum first{directories, special, none};
class Outputter {
private:
    void (*splitter)(std::vector<Entry>&, std::vector<Entry>&, std::vector<Entry>&);
    void (*sorter)(std::vector<Entry>&);
    bool reverse_order;
    std::string (*filename_formatter)(Entry&);
    void (*printer) (Entry&, std::string (*)(Entry&));
    void output_directory(Entry& dirent);

public:
    Outputter(ls_config& config);
    void output(std::vector<Entry>& entries);
};


#endif //MYLS_OUTPUTTER_H
