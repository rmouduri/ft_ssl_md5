#include <unistd.h>
#include <string.h>

#include "ft_ssl.h"

void print_help(void) {
    write(STDOUT_FILENO, FT_SSL_HELP, strlen(FT_SSL_HELP));
}

bool check_command(const char *command, ssl_t *ssl) {
    if (strcmp(MD5_COMMAND_ARG, command) == 0) {
        ssl->command = MD5;
    } else if (strcmp(SHA256_COMMAND_ARG, command) == 0) {
        ssl->command = SHA256;
    } else if (strcmp(HELP_ARG, command) == 0) {
        print_help();
        return false;
    } else {
        print_command_error(command);
        return false;
    }

    return true;
}

bool check_options(int argc, char **argv, ssl_t *ssl) {
    int i = 2;

    /* init ssl->ssl_strs */

    while (i < argc) {
        if (strcmp(HELP_ARG, argv[i]) == 0) {
            print_help();
            // free_ssl_strs(ssl->ssl_strs);
            return false;
        } else if (strcmp(P_OPTION_ARG, argv[i]) == 0) {
            ssl->options |= P_OPTION;
        } else if (strcmp(Q_OPTION_ARG, argv[i]) == 0) {
            ssl->options |= Q_OPTION;
        } else if (strcmp(R_OPTION_ARG, argv[i]) == 0) {
            ssl->options |= R_OPTION;
        } else if (strcmp(S_OPTION_ARG, argv[i]) == 0) {
            if (i + 1 >= argc) break;
            if (true/* Add to ssl->ssl_strs */ == false) {
                // free_ssl_strs(ssl->ssl_strs);
                return false;
            }
        } else {
            break;
        }

        ++i;
    }

    while (i < argc) {
        if (true/* Add to ssl->ssl_strs */ == false) {
            // free_ssl_strs(ssl->ssl_strs);
            return false;
        }

        ++i;
    }

    return true;
}

bool check_args(int argc, char **argv, ssl_t *ssl) {
    if (argc < 2) {
        print_usage();
        return false;
    }

    if (check_command(argv[1], ssl) == false) {
        return false;
    }

    if (check_options(argc, argv, ssl) == false) {
        return false;
    }

    return true;
}