//
// Created by arattel on 06.10.19.
//

#ifndef MYCAT_IO_H
#define MYCAT_IO_H

int read_file(const char *file_path, char **file_buf);
void output_error(const char* error_message);
int print(const char* message);

#endif //MYCAT_IO_H
