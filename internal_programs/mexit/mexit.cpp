//
// Created by arattel on 23.10.19.
//
#include "mexit.h"
#include <map>
#include "../../docopt/docopt.h"
#include <iostream>
#include "../../helpers/my_errno_values/my_errno.h"


static const char USAGE[] =
        R"(mexit
    Exits out of console
    Usage:
      mexit [<code>] [-h|--help]

    Options:
      -h --help     Show this screen.
)";
const std::string MEXIT = "mexit";
void run_mexit(std::vector<std::string> args){
    args = std::vector<std::string>(args.begin() + 1, args.end());
    try {
        std::map<std::string, docopt::value> args_parsed
                = docopt::docopt_parse(USAGE,
                                       args,
                                       false,               // show help if requested
                                       "mpwd");  // version string
        if(args_parsed["--help"].asBool()){
            std::cout << USAGE << std::endl;
        } else{
            if(args_parsed["<code>"]){
                exit(args_parsed["<code>"].asLong());
            } else{
                exit(0);
            }
        }
    } catch (const docopt::DocoptArgumentError& e){
        std::cerr << "Invalid argument" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
        std::cout << USAGE << std::endl;
    }
}