//
// Created by arattel on 08.11.19.
//

#include <zconf.h>
#include "pipe.h"
#include "../parsing/helpers.h"
#include "../parsing/parsing.h"
#include "../execution/execution.h"
#include "../filesystem/filesystem.h"
#include <iostream>
#include <wait.h>


void execute_pipe(std::string& input_line, std::set<std::string>& global, std::string& cur_path){
    std::vector<std::string> commands = split(input_line, "|");
    std::vector<std::vector<std::string>> commands_with_splitted_arguments;
    for(auto& command:commands){
        std::vector<std::string> command_args;
        get_command_line_args(command, command_args);
        commands_with_splitted_arguments.push_back(command_args);
    }
    piped_execution(commands_with_splitted_arguments, global, cur_path, dup(STDIN_FILENO),
            dup(STDOUT_FILENO), dup(STDERR_FILENO));
}

void piped_execution(std::vector<std::vector<std::string>>& all_piped_commands, std::set<std::string>& global,
                     std::string& cur_path, int saved_stdin, int saved_stdout, int saved_stderr){
    if(all_piped_commands.size() >= 2){
        int pipe_ends[2];
        pipe(pipe_ends);
        int read_end, write_end;
        read_end = pipe_ends[0];
        write_end = pipe_ends[1];

        pid_t pid = fork();
        if(pid == -1){
            std::cerr << "Error on fork" << std::endl;
        } else if(pid > 0){
            // parent process
            close(read_end);

            dup2(write_end, STDERR_FILENO);
            dup2(write_end, STDOUT_FILENO);

            execute_command(all_piped_commands[0], global, cur_path);

            close(write_end);

            int child_status;
            waitpid(pid, &child_status, 0);

            dup2(saved_stdout, STDOUT_FILENO);
            dup2(saved_stderr, STDERR_FILENO);
            dup2(saved_stdin, STDIN_FILENO);


        } else{
            // child process

            auto next_execution = std::vector<std::vector<std::string>>(all_piped_commands.begin() + 1,
                    all_piped_commands.end());

            close(write_end);
            dup2(read_end, STDIN_FILENO);

            piped_execution(next_execution, global, cur_path, saved_stdin, saved_stdout, saved_stderr);

            close(read_end);

            exit(0);
        }
    } else{
        dup2(saved_stdout, STDOUT_FILENO);
        dup2(saved_stderr, STDERR_FILENO);

        execute_command(all_piped_commands[0], global, cur_path);

        dup2(saved_stdin, STDIN_FILENO);
    }
}
