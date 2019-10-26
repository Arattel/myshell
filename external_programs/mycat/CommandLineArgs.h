//
// Created by arattel on 07.10.19.
//

#ifndef MYCAT_COMMANDLINEARGS_H
#define MYCAT_COMMANDLINEARGS_H

#include <vector>
#include <string>
#include <map>
#include <iostream>

class CommandLineArgs {
private:
    std::vector<std::map<std::vector<std::string>, std::string>> flags;
public:
    std::map<std::string, bool> flags_boolean;
    std::vector<std::string> other_arguments;


    CommandLineArgs(std::map<std::string, std::vector<std::string>> flags, const char** arguments, int argc){
        flags = flags;
        for(auto& pair:flags){
            flags_boolean[pair.first] = false;
        }
        for(int i = 1; i < argc; i++){
            std::string argument = arguments[i];

            bool is_flag = false;
            for(auto& equal_flags:flags){
                std::vector<std::string>& synonimic_flags = equal_flags.second;
                std::string& label = const_cast<std::string &>(equal_flags.first);
                for(auto& flag:synonimic_flags){

                    if(argument == flag){
                        flags_boolean[label] = true;
                        is_flag = true;
                    }
                }
            }
            if(!is_flag){
                other_arguments.push_back(argument);
            }
        }
    }
};


#endif //MYCAT_COMMANDLINEARGS_H
