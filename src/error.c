#include <unistd.h>
#include <string.h>

#include "ft_ssl.h"


void print_usage(void) {
    write(STDERR_FILENO, FT_SSL_USAGE, strlen(FT_SSL_USAGE));
}

void print_command_error(const char *command) {
    write(STDERR_FILENO, FT_SSL_INVALID_COMMAND_1, strlen(FT_SSL_INVALID_COMMAND_1));
    write(STDERR_FILENO, command, strlen(command));
    write(STDERR_FILENO, FT_SSL_INVALID_COMMAND_2, strlen(FT_SSL_INVALID_COMMAND_2));
}

void print_malloc_error(const char *function) {
    write(STDERR_FILENO, "Malloc error in function: ", strlen("Malloc error in function: "));
    write(STDERR_FILENO, function, strlen(function));
    write(STDERR_FILENO, "\n", 1);
}

void print_read_error(const char *function) {
    write(STDERR_FILENO, "Read error in function: ", strlen("Read error in function: "));
    write(STDERR_FILENO, function, strlen(function));
    write(STDERR_FILENO, "\n", 1);
}