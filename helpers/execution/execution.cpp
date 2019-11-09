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
#include "../parsing/parsing.h"
#include "../parsing/helpers.h"
#include "../pipe/pipe.h"
#include "../variables/variables.h"
#include "../filesystem/filesystem.h"

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <fstream>


void execute_command(std::vector<std::string>& args, std::set<std::string>& global, std::set<std::string>& local,
        std::string& cur_path){
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
        }else if(args[0] == "."){
            execute_script(args[1], global, local, cur_path);
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
            execute_command(args, global, local, cur_path);
            exit(0);
        }
    }

}

void execute_line(std::string& input, std::set<std::string>& global, std::set<std::string>& local,
        std::string& cur_path){
    input = trim_comment(input);
    if(substring_in_string(input, "|")){
        execute_pipe(input, global,local, cur_path);
    } else{
        if(is_assignment(input)){
            std::string varname, value;
            split_assignment(input, varname, value);
            if(is_command_for_variable(value)){
                std::string command = value.substr(2, value.size() - 3);

                int saved_stdout  = dup(STDOUT_FILENO);
                int fd[2];
                pipe(fd);
                int read_end = fd[0];
                int write_end = fd[1];
                dup2(write_end, STDOUT_FILENO);

                std::vector<std::string> command_args;
                get_command_line_args(command, command_args);
                execute_command(command_args, global, local, cur_path);
                close(write_end);

                char bf[38];
                read(read_end, bf, 38);
                value = read_file_into_string(read_end);
                close(read_end);
                dup2(saved_stdout, STDOUT_FILENO);

                setenv(varname.c_str(), value.c_str(), true);


            }else{
                setenv(varname.c_str(), value.c_str(), true);
            }
            local.insert(varname);
        }else{

            std::vector<std::string> args;
            int status = get_command_line_args(input, args);
            if(!status){
                if(args.empty()){
                    std::cerr << "No valid arguments provided" << std::endl;
                }
                else{

                    execute_command(args, global, local, cur_path);
                }
            }
        }
    }
}


std::string read(std::string& filename) {
    std::fstream input_file_stream;
    path_to_global_external(filename);
    input_file_stream.open(filename);
    if (input_file_stream.is_open()) {
        auto const start_pos = input_file_stream.tellg();
        input_file_stream.ignore(std::numeric_limits<std::streamsize>::max());
        auto const char_count = input_file_stream.gcount();
        input_file_stream.seekg(start_pos);
        auto input_string = std::string(char_count, char{});
        input_file_stream.read(&input_string[0], input_string.size());
        return input_string;
    } else{
        return "";
    }
}
std::vector<std::string> get_lines(std::string& file_contents){
    return split(file_contents, "\n");
}

void execute_script(std::string filename,  std::set<std::string>& global, std::set<std::string>& local,
                    std::string& cur_path){
    auto contents  = read(filename);
    auto commands  = get_lines(contents);
    for(auto& command:commands){
        command = boost::trim_copy(command);
        if(command.size() > 0){
            execute_line(command, global, local, cur_path);
        }
    }
}
