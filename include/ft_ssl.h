#include <stdint.h>
#include <stdbool.h>

#ifndef _FT_SSL_
# define _FT_SSL_


# define FT_SSL     "ft_ssl"
# define ECHO_STDIN_ARG     "-p"
# define QUIET_MODE_ARG     "-q"
# define REVERSE_MODE_ARG   "-r"
# define STRING_ARG         "-s"
# define HELP_ARG           "-h"
# define MD5_COMMAND_ARG    "md5"
# define SHA256_COMMAND_ARG "sha256"
# define FT_SSL_HELP    "help\n"
# define FT_SSL_USAGE   "usage: "FT_SSL" command [flags] [FILE_INPUT/string]\n"
# define FT_SSL_INVALID_COMMAND_1   FT_SSL": Error: '"
# define FT_SSL_INVALID_COMMAND_2   "' is an invalid command.\n\n" \
                        "Commands:\n" \
                        MD5_COMMAND_ARG"\n" \
                        SHA256_COMMAND_ARG"\n\n" \
                        "Flags:\n" \
                        "-p -q -r -s\n"


# define ALGO_STRING { \
    "MD5", \
    "SHA256" \
}

typedef enum ssl_encrypt_algo_s {
    MD5,
    SHA256
} ssl_encrypt_algo_t;

typedef enum ssl_option_e {
    ECHO_STDIN_OPTION   = 1 << 0,
    QUIET_MODE_OPTION   = 1 << 1,
    REVERSE_MODE_OPTION = 1 << 2
} ssl_option_t;

typedef enum ssl_input_type_e {
    STDIN_INPUT,
    ARG_INPUT,
    FILE_INPUT
} ssl_input_type_t;

typedef struct ssl_input_s {
    uint8_t             *hash;
    uint8_t             *ssl_str;
    const char          *ssl_arg;
    uint64_t            len;
    ssl_input_type_t    type;
    ssl_encrypt_algo_t  encrypt_algo;
    struct ssl_input_s  *next;
} ssl_input_t;

typedef struct ssl_s {
    ssl_encrypt_algo_t  algo;
    ssl_option_t        options;
    ssl_input_t         *ssl_inputs;
} ssl_t;


/* option.c */
int check_args(int argc, char **argv, ssl_t *ssl);
void free_ssl_inputs(ssl_input_t *ssl_inputs);

/* error.c */
void print_usage(void);
void print_command_error(const char *command);
void print_malloc_error(const char *function);
void print_read_error(const char *function);

#endif // _FT_SSL_
