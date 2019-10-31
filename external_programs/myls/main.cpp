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

std::string USAGE = R""""(
myls
    Lists all given files/files in given directories
    Usage:
      myls [path|mask] [-l] [-h|--help] [--sort=U|S|t|X|D|s] [-r] [-F][-R]


    Options:
      -h --help     Show this screen.
      -l            Detailed info
      -F            Show characters for special files
      -r            Reverse sort order
      -R            Recursive walk(for directories)
      --sort=:
             U - unsorted
             S - by size
             t - by modification time
             X - by extension
             N - by name
             D - directories first
             s - special files first
)"""";

int main(int argc, char** argv){
    ls_config config = ls_config();
    if(parse_config(argc, argv, config)){
        return 1;
    }
    if(config.show_help){
        std::cout << USAGE << std::endl;
    } else{
        std::vector<Entry> entries;
        filter_nonexistent_files_vector(config.filenames);
        walk_files(entries, config);
        Outputter out = Outputter(config);
        out.output(entries);
    }
    return 0;
}