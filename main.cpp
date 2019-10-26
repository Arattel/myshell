//
// Created by arattel on 20.10.19.
//

#include <iostream>
#include "helpers/io/console_io.h"
#include "helpers/parsing/parsing.h"
#include <vector>
#include "internal_programs/mpwd/mpwd.h"
#include "internal_programs/merrno/merrno.h"
#include "internal_programs/mcd/mcd.h"
#include "internal_programs/mexit/mexit.h"
#include "internal_programs/mecho/mecho.h"
#include "internal_programs/mexport/mexport.h"


#include <cstdlib>
#include <readline/readline.h>
#include <readline/history.h>
#include <set>
#include "helpers/my_errno_values/my_errno.h"
#include "helpers/parsing/helpers.h"
#include "helpers/variables/variables.h"
#include "external_programs/external.h"

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
                else if(args[0] == MERRNO){
                    run_merrno(args);
                } else if(args[0] == MCD){
                    run_mcd(args, cur_path);
                }
                else if(args[0] == MPWD){
                    run_mpwd(args);
                }else if(args[0] == MEXIT){
                    run_mexit(args);
                } else if(args[0] ==  MECHO){
                    run_mecho(args);
                } else if(args[0] == MEXPORT){
                    run_mexport(args, global);
                }
                else{
                    std::string pth;
                    if(is_local_external(args[0])){
                        pth = path_to_local_external(args[0]);
                        run_external(pth, args, global);
                    } else if(is_global_external(args[0])){
                        pth = path_to_global_external(args[0]);
                        run_external(pth, args, global);
                    }
                    else{
                        std::cerr << "Invalid command" << std::endl;
                    }
                }
            }
        }
        free(buf);
    }
        return 0;
    }

