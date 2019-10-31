//
// Created by arattel on 30.10.19.
//

#ifndef MYLS_FILE_H
#define MYLS_FILE_H
#include <boost/filesystem.hpp>
#include <string>
#include <vector>
#include "../config/config.h"
#include <sys/stat.h>


namespace fs = boost::filesystem;
enum file_type{file, executable, symlink_type, named_pipe, socket, directory, other};
class Entry {
public:
    file_type type;
    size_t size;
    struct timespec last_modified;
    std::string name;
    std::vector<Entry> children;
    Entry(std::string filename, ls_config& cfg, bool is_subdir);

};
int can_exec(std::string file);
int exists(std::string path);
void list_files_in_directory(std::string dir_name, std::vector<Entry>& files, ls_config& conf);
void walk_files(std::vector<Entry>& entries, ls_config& cfg);
void get_file_type(struct stat& file_data, file_type& type, std::string& filename);
std::string combine(std::string dir, std::string file);
#endif //MYLS_FILE_H
