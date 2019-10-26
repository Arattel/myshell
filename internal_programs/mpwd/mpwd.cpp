//
// Created by arattel on 21.10.19.
//

#include "mpwd.h"
#include "../../docopt/docopt.h"
#include <iostream>
#include <map>
#include <cstdlib>
#include "../../helpers/my_errno_values/my_errno.h"


extern const std::string MPWD = "mpwd";
static const char USAGE[] =
        R"(mpwd

    Usage:
      mpwd [-h|--help]

    Options:
      -h --help     Show this screen.
)";

void run_mpwd(std::vector<std::string> args){
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
            std::cout << getenv("PATH") << std::endl;
        }
        setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    } catch (const docopt::DocoptArgumentError& e){
        std::cerr << "Invalid argument" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
        std::cout << USAGE << std::endl;
    }

}




