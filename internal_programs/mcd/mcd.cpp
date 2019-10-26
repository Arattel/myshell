//
// Created by arattel on 23.10.19.
//
#include "mcd.h"
#include "../../helpers/filesystem/filesystem.h"

const std::string MCD = "mcd";


#include <map>
#include "../../docopt/docopt.h"
#include <iostream>
#include "../../helpers/my_errno_values/my_errno.h"

const std::string MERRNO = "merrno";

static const char USAGE[] =
        R"(mcd
    Changes current path
    Usage:
      mcd [-h|--help] <path>
      mcd <path> [-h|--help]
      mcd [-h|--help]

    Options:
      -h --help     Show this screen.
)";

void run_mcd(std::vector<std::string> args, std::string& cur_path){
    args = std::vector<std::string>(args.begin() + 1, args.end());
    try {
        std::map<std::string, docopt::value> args_parsed
                = docopt::docopt_parse(USAGE,
                                       args,
                                       false,               // show help if requested
                                       "mcd");  // version string
        if(args_parsed["--help"].asBool()){
            std::cout << USAGE << std::endl;
            setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
        } else{
            std::string absolute_path = getenv("PATH"), abspath, relpath;
            relpath = args_parsed["<path>"].asString();
            int  status = get_absolute_path(relpath, absolute_path, abspath);

            if(!status){
                abspath = abspath.substr(0, abspath.size() - 1);
                cur_path = abspath;
                setenv("PATH", abspath.c_str(), true);
                setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
            } else{
                setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
                std::cerr << "Invalid path, cannot change" << std::endl;
            }
        }
    } catch (const docopt::DocoptArgumentError& e){
        std::cerr << "Invalid argument" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
        std::cout << USAGE << std::endl;
    }
}
