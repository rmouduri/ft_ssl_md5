#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

#include "ft_ssl.h"


void free_ssl_inputs(ssl_input_t *ssl_inputs) {
    ssl_input_t *tmp;

    while (ssl_inputs) {
        tmp = ssl_inputs;
        ssl_inputs = ssl_inputs->next;

        if (tmp->type != ARG_INPUT && tmp->ssl_str) {
            free(tmp->ssl_str);
        }

        if (tmp->hash) {
            free(tmp->hash);
        }

        free(tmp);
    }
}

static int8_t read_fd(int fd, uint8_t **dest, uint64_t *len) {
    uint8_t buffer[256];
    uint8_t *tmp = NULL;
    int64_t r;

    *len = 0;
    while ((r = read(fd, buffer, 256)) > 0) {
        if (*len && (tmp = malloc(sizeof(uint8_t) * (*len))) == NULL) {
            if (*dest) { free(*dest); }
            *dest = NULL;
            return -1;
        }

        memcpy(tmp, *dest, *len);

        if (*dest) { free(*dest); }
        if ((*dest = malloc(sizeof(uint8_t) * (*len + r))) == NULL) {
            if (tmp) { free(tmp); }
            return -1;
        }

        memcpy(*dest, tmp, *len);
        memcpy(*dest + *len, buffer, r);

        if (tmp) { free(tmp); }
        tmp = NULL;

        *len += r;
    }

    if (r == -1) {
        if (*dest) { free(*dest); }
        print_read_error("read_fd");
        return -1;
    }

    return 0;
}

static int add_entry(ssl_t *ssl, const char *input, ssl_input_type_t type) {
    ssl_input_t *tmp = ssl->ssl_inputs;
    ssl_input_t *new_entry;

    while (tmp && tmp->next) { tmp = tmp->next; }

    if ((new_entry = malloc(sizeof(ssl_input_t))) == NULL) {
        print_malloc_error("add_entry");
        return -1;
    }

    new_entry->ssl_str = NULL;

    new_entry->encrypt_algo = ssl->algo;
    new_entry->type = type;
    new_entry->ssl_arg = input;
    new_entry->hash = NULL;
    new_entry->next = NULL;

    if (type == ARG_INPUT) {
        new_entry->ssl_str = (uint8_t *) input;
        new_entry->len = strlen((char *) new_entry->ssl_str);
    } else if (type == FILE_INPUT) {
        int fd;
        new_entry->len = 1;
        if ((fd = open(input, O_RDONLY)) != -1
                && read_fd(fd, &new_entry->ssl_str, &new_entry->len) == -1) {
            return -1;
        }
        close(fd);
    } else if (type == STDIN_INPUT) {
        if (read_fd(STDIN_FILENO, &new_entry->ssl_str, &new_entry->len) == -1) {
            free(new_entry);
            return -1;
        }

        new_entry->next = ssl->ssl_inputs;
        ssl->ssl_inputs = new_entry;
    }

    if (type != STDIN_INPUT) {
        if (tmp) {
            tmp->next = new_entry;
        } else {
            ssl->ssl_inputs = new_entry;
        }
    }

    return 0;
}

static void print_help(void) {
    write(STDOUT_FILENO, FT_SSL_HELP, strlen(FT_SSL_HELP));
}

static int check_command(const char *command, ssl_t *ssl) {
    if (strcmp(MD5_COMMAND_ARG, command) == 0) {
        ssl->algo = MD5;
    } else if (strcmp(SHA256_COMMAND_ARG, command) == 0) {
        ssl->algo = SHA256;
    } else if (strcmp(HELP_ARG, command) == 0) {
        print_help();
        return -1;
    } else {
        print_command_error(command);
        return -1;
    }

    return 0;
}

int check_options(int argc, char **argv, ssl_t *ssl) {
    int i = 2;

    while (i < argc) {
        if (strcmp(HELP_ARG, argv[i]) == 0) {
            print_help();
            free_ssl_inputs(ssl->ssl_inputs);
            return -1;
        } else if (strcmp(ECHO_STDIN_ARG, argv[i]) == 0
                && !(ssl->options & ECHO_STDIN_OPTION)) {
            ssl->options |= ECHO_STDIN_OPTION;
            if (add_entry(ssl, NULL, STDIN_INPUT) == -1) {
                free_ssl_inputs(ssl->ssl_inputs);
                return -1;
            }
        } else if (strcmp(QUIET_MODE_ARG, argv[i]) == 0) {
            ssl->options |= QUIET_MODE_OPTION;
        } else if (strcmp(REVERSE_MODE_ARG, argv[i]) == 0) {
            ssl->options |= REVERSE_MODE_OPTION;
        } else if (strcmp(STRING_ARG, argv[i]) == 0) {
            if (i + 1 >= argc) break;
            if (add_entry(ssl, argv[++i], ARG_INPUT) == -1) {
                free_ssl_inputs(ssl->ssl_inputs);
                return -1;
            }
        } else {
            break;
        }

        ++i;
    }

    while (i < argc) {
        if (add_entry(ssl, argv[i], FILE_INPUT) == -1) {
            free_ssl_inputs(ssl->ssl_inputs);
            return -1;
        }

        ++i;
    }

    if (ssl->ssl_inputs == NULL && add_entry(ssl, NULL, STDIN_INPUT) == -1) {
        return -1;
    }

    return 0;
}

int check_args(int argc, char **argv, ssl_t *ssl) {
    if (argc < 2) {
        print_usage();
        return -1;
    }

    if (check_command(argv[1], ssl) == -1) {
        return -1;
    }

    if (check_options(argc, argv, ssl) == -1) {
        return -1;
    }

    return 0;
}