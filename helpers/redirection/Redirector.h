//
// Created by arattel on 07.11.19.
//

#ifndef MYSHELL_REDIRECTOR_H
#define MYSHELL_REDIRECTOR_H

#include <vector>
#include <string>


class Redirector {
private:
    std::vector<std::vector<int>> from_to;

public:
    Redirector(std::vector<std::string>& redirections);
    void redirect();
    void recover();
};

std::vector<int> get_redirection(std::string& redirection);
#endif //MYSHELL_REDIRECTOR_H
