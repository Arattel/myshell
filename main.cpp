//
// Created by arattel on 20.10.19.
//

#include <iostream>
#include "helpers/io/console_io.h"
#include "helpers/parsing/parsing.h"
#include <vector>
#include "internal_programs/mexport/mexport.h"


#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <set>
#include <zconf.h>
#include <fcntl.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include "helpers/my_errno_values/my_errno.h"
#include "helpers/parsing/helpers.h"
#include "helpers/variables/variables.h"
#include "helpers/execution/execution.h"
#include "helpers/redirection/redirection.h"
#include "helpers/redirection/Redirector.h"
#include "helpers/filesystem/filesystem.h"
#include "helpers/pipe/pipe.h"
char* readLine();

int main(int argc, char** argv){
    auto cur_path = get_current_path();
    setenv("PATH", cur_path.c_str(), true);
    setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    setenv("DEFAULT_PATH", cur_path.c_str(), true);
    std::set<std::string> local;
    std::set<std::string> global = {"PATH", "ERRNO", "DEFAULT_PATH"};
    char* buf;

    while ((buf = readline((cur_path + " $").c_str())) != nullptr){
        std::string input(buf);
        if(strlen(buf) > 0){
            add_history(input.c_str());
        }
        if(substring_in_string(input, "|")){
            execute_pipe(input, global, cur_path);
        } else{
            std::vector<std::string> args;
            int status = get_command_line_args(input, args);
            if(!status){
                if(args.empty()){
                    std::cerr << "No valid arguments provided" << std::endl;
                } else{
                    if(is_assignment(args[0])){
                        std::string varname, value;
                        split_assignment(args[0], varname, value);
                        setenv(varname.c_str(), value.c_str(), true);
                        local.insert(varname);
                    }
                    else{

                        execute_command(args, global, cur_path);
                    }
                }
            }
        }
        free(buf);
    }
        return 0;
    }
