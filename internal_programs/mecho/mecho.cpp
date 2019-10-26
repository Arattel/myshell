//
// Created by arattel on 23.10.19.
//

#include <map>
#include "../../docopt/docopt.h"
#include <iostream>
#include "../../helpers/my_errno_values/my_errno.h"
#include "mecho.h"


const std::string MECHO = "mecho";

static const char USAGE[] =
        R"(mecho
    Outputs  arguments(arguments can be both variables($PATH) and words
    Usage:
      mecho [<args>...] [-h|--help]
      mecho [<args>...] [-h|--help] [<args>...]
      mecho [-h|--help] [<args>...]

    Options:
      -h --help     Show this screen.
)";

void run_mecho(std::vector<std::string> args){
    args = std::vector<std::string>(args.begin() + 1, args.end());
    try {
        std::map<std::string, docopt::value> args_parsed
                = docopt::docopt_parse(USAGE,
                                       args,
                                       false,               // show help if requested
                                       "mecho");  // version string
        if(args_parsed["--help"].asBool()){
            std::cout << USAGE << std::endl;
        } else{
            for(auto& str: args_parsed["<args>"].asStringList()){
                std::cout << str << std::endl;
            }
        }
        setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    } catch (const docopt::DocoptArgumentError& e){
        std::cerr << "Invalid argument" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
        std::cout << USAGE << std::endl;
    }
}
