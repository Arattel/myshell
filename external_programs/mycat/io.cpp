//
// Created by arattel on 06.10.19.
//
#include "io.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <cstdlib>


int read_file(const char *file_path, char **file_buf) {
    int fd;
    ssize_t file_size, numRead;
    struct stat stbuf;

    fd = open(file_path, O_RDONLY);
    if (fd == -1) {
        if (errno == EINTR) {
            output_error("Opening file was interrupted by signal");
            return 1;
        } else {
            output_error("Error opening file");
            return 1;
        }
    }
    fstat(fd, &stbuf);
    file_size = stbuf.st_size;
    *file_buf = (char *) calloc(file_size, sizeof(char));
    numRead = read(fd, *file_buf, file_size);
    if (numRead == -1 or numRead != file_size) {
        if (errno == EINTR || numRead < file_size) {
            output_error("Reading file was interrupted by signal");
            return 1;
        } else {
            output_error("Error reading file");
            return 1;
        }
    }
    close(fd);
    return 0;
}

void output_error(const char *error_message) {
    off_t num_written = write(STDERR_FILENO, error_message, strlen(error_message));
    if (num_written == -1) {
        if (errno == EINTR) {
            output_error(error_message);
        }
    }
}

int print(const char *message) {
    size_t message_len = strlen(message);
    off_t num_written = write(STDOUT_FILENO, message, message_len);
    if (num_written == -1 || num_written < message_len) {
        if (errno == EINTR || num_written < message_len) {
            output_error("Writing to console was interrupted by signal");
            return 1;
        } else {
            output_error("Error writing to console");
            return 1;
        }
    }
    return 0;
}



