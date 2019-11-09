//
// Created by arattel on 07.11.19.
//

#include <iostream>
#include <zconf.h>
#include "execution.h"
#include "../../internal_programs/mpwd/mpwd.h"
#include "../../internal_programs/merrno/merrno.h"
#include "../../internal_programs/mcd/mcd.h"
#include "../../internal_programs/mexit/mexit.h"
#include "../../internal_programs/mecho/mecho.h"
#include "../../internal_programs/mexport/mexport.h"
#include "../../external_programs/external.h"
#include "../redirection/Redirector.h"
#include "../redirection/redirection.h"
#include <algorithm>



void execute_command(std::vector<std::string>& args, std::set<std::string>& global, std::string& cur_path){
    if(args[args.size() - 1] != "&"){
        auto redir = redirect_output(args);
        Redirector r = Redirector(redir);
        r.redirect();
        if(args[0] == MERRNO){
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
        r.recover();
    } else{
        pid_t  pid = fork();
        if(pid == -1){
            std::cerr << "Error on fork" << std::endl;
        } else if(pid == 0){
            // child
            Redirector r = Redirector(args);
            auto redirected = r.get_redirected();
            int desc[] = {STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO};
            int desc_size = 3;
            for(int i = 0; i < desc_size; i++){
                if(std::find(redirected.begin(), redirected.end(), desc[i]) == redirected.end()){
                    close(desc[i]);
                }
            }
            execute_command(args, global, cur_path);
            exit(0);
        }
    }

}
