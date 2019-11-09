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

int main(int argc, char** argv){
    auto cur_path = get_current_path();

    setenv("PATH", cur_path.c_str(), true);
    setenv("ERRNO", std::to_string(ERRNO_OK).c_str(), true);
    setenv("DEFAULT_PATH", cur_path.c_str(), true);
    std::set<std::string> local;
    std::set<std::string> global = {"PATH", "ERRNO", "DEFAULT_PATH"};
    if(argc > 1){
        execute_script(argv[1], global, local, cur_path);
    }
    char* buf;

    while ((buf = readline((cur_path + " $").c_str())) != nullptr){
        std::string input(buf);
        if(strlen(buf) > 0){
            add_history(input.c_str());
        }
        execute_line(input, global, local, cur_path);
        free(buf);
    }
        return 0;
    }
