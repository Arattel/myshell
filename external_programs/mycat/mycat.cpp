#include "io_string.h"
#include "io.h"
#include <map>
#include <vector>
#include <string>
#include "CommandLineArgs.h"
#include "fitering.h"
#include "path_transform.h"


int main(int argc, const char **argv) {

    std::map<std::string, std::vector<std::string>> const flags_dict{
            {"help",        {"-h", "--help"}},
            {"hexadecimal", {"-A"}}
    };

    static const char USAGE[] =
            R"(mycat
    This program reads files given as command line arguments and outputs them to stdout

    Usage:
      mycat <files>...
      mycat (-h | --help)

    Options:
      -h / --help     Show this screen.
      -A            All non-printable characters are outputted as their hexadecimal codes
)";


    CommandLineArgs my_args = CommandLineArgs(flags_dict, argv, argc);

    if (my_args.flags_boolean["help"]) {
        print(USAGE);
    } else{
        bool hex = false;
        if(my_args.flags_boolean["hexadecimal"]){
            hex = true;
        }
        std::vector<std::string> outputs;
       for(std::string& file_path : my_args.other_arguments){
           std::string absolute_path;
           int path_exists = get_absolute_path(file_path, absolute_path);
           if(path_exists != 0){
               output_error("File doesn't exist");
               return path_exists;
           }
           std::string file_text;
           int read_status = read_file_to_string(absolute_path, file_text);
           if(read_status != 0){
               return read_status;
           } else{
               if(hex){
                   file_text = filter_nonprintable_hex(file_text);
                   outputs.push_back(file_text);
               } else{
                   outputs.push_back(file_text);
               }
           }
       }
       for(std::string& output_file:outputs){
           int print_status = print_str(output_file);
           if(print_status != 0){
               return print_status;
           }
       }
    }
    return 0;
}