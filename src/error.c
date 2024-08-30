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