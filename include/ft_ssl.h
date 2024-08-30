#include <stdint.h>
#include <stdbool.h>

#ifndef _FT_SSL_
# define _FT_SSL_


# define FT_SSL     "ft_ssl"
# define P_OPTION_ARG   "-p"
# define Q_OPTION_ARG   "-q"
# define R_OPTION_ARG   "-r"
# define S_OPTION_ARG   "-s"
# define HELP_ARG       "-h"
# define MD5_COMMAND_ARG    "md5"
# define SHA256_COMMAND_ARG "sha256"
# define FT_SSL_HELP    "help\n"
# define FT_SSL_USAGE   "usage: "FT_SSL" command [flags] [file/string]\n"
# define FT_SSL_INVALID_COMMAND_1   FT_SSL": Error: '"
# define FT_SSL_INVALID_COMMAND_2   "' is an invalid command.\n\n" \
                        "Commands:\n" \
                        MD5_COMMAND_ARG"\n" \
                        SHA256_COMMAND_ARG"\n\n" \
                        "Flags:\n" \
                        "-p -q -r -s\n"


typedef enum ssl_command_e {
    MD5,
    SHA256
} ssl_command_t;

typedef enum ssl_option_e {
    P_OPTION = 1 << 0,
    Q_OPTION = 1 << 1,
    R_OPTION = 1 << 2,
    S_OPTION = 1 << 3,
} ssl_option_t;

typedef enum ssl_str_type_e {
    STDIN_STR,
    ARG_STR,
    FILE
} ssl_type_t;

typedef struct ssl_str_s {
    char            *ssl_str;
    const char      *ssl_arg;
    ssl_type_t      type;
    struct ssl_str_s    *next;
} ssl_str_t;

typedef struct ssl_s {
    ssl_command_t   command;
    ssl_option_t    options;
    ssl_str_t       *ssl_strs;
} ssl_t;


/* option.c */
bool check_args(int argc, char **argv, ssl_t *ssl);

/* error.c */
void print_usage(void);
void print_command_error(const char *command);


#endif // _FT_SSL_