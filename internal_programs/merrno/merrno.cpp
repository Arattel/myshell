//
// Created by arattel on 23.10.19.
//
#include "merrno.h"
#include <map>
#include "../../docopt/docopt.h"
#include <iostream>
#include "../../helpers/my_errno_values/my_errno.h"

const std::string MERRNO = "merrno";

static const char USAGE[] =
        R"(merrno
    Outputs  current errno
    Usage:
      merrno [-h|--help]

    Options:
      -h --help     Show this screen.
)";

void run_merrno(std::vector<std::string> args){
    args = std::vector<std::string>(args.begin() + 1, args.end());
    try {
        std::map<std::string, docopt::value> args_parsed
                = docopt::docopt_parse(USAGE,
                                       args,
                                       false,               // show help if requested
                                       "merrno");  // version string
        if(args_parsed["--help"].asBool()){
            std::cout << USAGE << std::endl;
        } else{
            std::cout << getenv("ERRNO") << std::endl;
        }
        setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    } catch (const docopt::DocoptArgumentError& e){
        std::cerr << "Invalid argument" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
        std::cout << USAGE << std::endl;
    }
}
