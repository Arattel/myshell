//
// Created by arattel on 26.10.19.
//
#include "config/config.h"
#include "filesystem_classes/Entry.h"
#include "filesystem_classes/filesystem.h"
#include <iostream>
#include <boost/filesystem.hpp>
#include "outputter/output.h"
#include "outputter/Outputter.h"

namespace fs = boost::filesystem;

int main(int argc, char** argv){
    ls_config config = ls_config();
    if(parse_config(argc, argv, config)){
        return 1;
    }

    std::vector<Entry> entries;
    filter_nonexistent_files_vector(config.filenames);
    walk_files(entries, config);
    Outputter out = Outputter(config);
    out.output(entries);
    return 0;
}