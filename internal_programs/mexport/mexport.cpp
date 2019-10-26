#include "mexport.h"
#include <map>
#include "../../docopt/docopt.h"
#include <iostream>
#include "../../helpers/my_errno_values/my_errno.h"
#include "../../helpers/parsing/helpers.h"
#include "../../helpers/variables/variables.h"



const std::string MEXPORT = "mexport";
static const char USAGE[] =
        R"(mexport
    Sets global variable(VAR=VALUE)
    Usage:
      mecho [<var>] [-h|--help]
      mecho [-h|--help] [<var>]

    Options:
      -h --help     Show this screen.
)";


void run_mexport(std::vector<std::string> args, std::set<std::string>& global){
    args = std::vector<std::string>(args.begin() + 1, args.end());
    try {
        std::map<std::string, docopt::value> args_parsed
                = docopt::docopt_parse(USAGE,
                                       args,
                                       false,               // show help if requested
                                       "mexport");  // version string
        if(args_parsed["--help"].asBool()){
            std::cout << USAGE << std::endl;
        } else{
            std::string str = args_parsed["<var>"].asString();
            if(substring_in_string(str, "=")){
                std::string value, varname;
                split_assignment(str, varname, value);
                setenv(varname.c_str(), value.c_str(), true);
                global.insert(str);
            } else{
                setenv(str.c_str(), "", true);
                global.insert(str);
            }
        }
        setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    } catch (const docopt::DocoptArgumentError& e){
        std::cerr << "Invalid argument" << std::endl;
        setenv("ERRNO", std::to_string(ERRNO_WRONG_ARGUMENTS).c_str(), true);
        std::cout << USAGE << std::endl;
    }
}
