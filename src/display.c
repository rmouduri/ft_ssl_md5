#include <stdio.h>
#include <ctype.h>

#include "ft_ssl.h"
#include "display.h"

void ft_hexdump(const void *ptr, int size) {
    const unsigned char *buffer = (unsigned char *) ptr;
    int i, j;

    for (i = 0; i < size; i += 16) {
        ft_printf("%08x  ", i);

        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                ft_printf("%02x ", buffer[i + j]);
            } else {
                ft_printf("   ");
            }
        }

        ft_printf(" ");

        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                const unsigned char ch = buffer[i + j];
                if (isprint(ch)) {
                    ft_printf("%c", ch);
                } else {
                    ft_printf(".");
                }
            }
        }

        ft_printf("\n");
    }
}

void ft_binarydump(const void *ptr, int size) {
    const unsigned char *buffer = (unsigned char *) ptr;
    int i, j;

    for (i = 0; i < size; i += 8) {
        ft_printf("%08x  ", i);

        for (j = 0; j < 8; j++) {
            if (i + j < size) {
                const unsigned char byte = buffer[i + j];
                for (int bit = 7; bit >= 0; bit--) {
                    ft_printf("%d", (byte >> bit) & 1);
                }
                ft_printf(" ");
            } else {
                ft_printf("         ");
            }
        }

        ft_printf(" ");

        for (j = 0; j < 8; j++) {
            if (i + j < size) {
                const unsigned char ch = buffer[i + j];
                if (isprint(ch)) {
                    ft_printf("%c", ch);
                } else {
                    ft_printf(".");
                }
            }
        }

        ft_printf("\n");
    }
}

static void display_hash(const uint8_t *hash, ssl_encrypt_algo_t algo) {
    uint64_t size;

    if (algo == MD5) {
        size = 128;
    } else if (algo == SHA256) {
        size = 256;
    }

    for (uint64_t i = 0; i < (size / 8); ++i) {
        ft_printf("%02x", hash[i]);
    }
}

static void print_no_esc_char(uint8_t *input) {
    while (*input) {
        if (isprint(*input)) {
            ft_printf("%c", *input);
        }

        ++input;
    }
}

static void display_arg_input(const ssl_input_t *input, ssl_encrypt_algo_t algo, ssl_option_t options) {
    const char algo_strings[2][16] = ALGO_STRING;

    if (!(options & QUIET_MODE_OPTION) && !(options & REVERSE_MODE_OPTION)) {
        ft_printf("%s (\"", algo_strings[algo]);
        print_no_esc_char(input->ssl_str);
        ft_printf("\") = ");
    }

    display_hash(input->hash, algo);

    if (!(options & QUIET_MODE_OPTION) && options & REVERSE_MODE_OPTION) {
        ft_printf(" \"");
        print_no_esc_char(input->ssl_str);
        ft_printf("\"");
    }

    ft_printf("\n");
}

static void display_file_input(const ssl_input_t *input, ssl_encrypt_algo_t algo, ssl_option_t options) {
    const char algo_strings[2][16] = ALGO_STRING;

    if (!(options & QUIET_MODE_OPTION) && !(options & REVERSE_MODE_OPTION)) {
        ft_printf("%s (", algo_strings[algo]);
        print_no_esc_char((uint8_t *) input->ssl_arg);
        ft_printf(") = ");
    }

    display_hash(input->hash, algo);

    if (!(options & QUIET_MODE_OPTION) && options & REVERSE_MODE_OPTION) {
        ft_printf(" ");
        print_no_esc_char((uint8_t *) input->ssl_arg);
    }

    ft_printf("\n");
}

static void display_stdin_input(const ssl_input_t *input, ssl_encrypt_algo_t algo, ssl_option_t options) {
    if (!(options & QUIET_MODE_OPTION)) {
        if (options & ECHO_STDIN_OPTION) {
            ft_printf("(\"");
            print_no_esc_char(input->ssl_str);
            ft_printf("\")= ");
        } else {
            ft_printf("(stdin)= ");
        }
    } else if (options & ECHO_STDIN_OPTION) {
        print_no_esc_char(input->ssl_str);
        ft_printf("\n");
    }

    display_hash(input->hash, algo);
    ft_printf("\n");
}

void display(const ssl_input_t *input, ssl_encrypt_algo_t algo, ssl_option_t options) {
    if (input->type == FILE_INPUT && input->ssl_str == NULL && input->len == 1) {
        ft_printf(SSL_NO_FILE_DIRECTORY, input->ssl_arg);
        return ;
    }

    if (input->type == ARG_INPUT) {
        display_arg_input(input, algo, options);
    } else if (input->type == FILE_INPUT) {
        display_file_input(input, algo, options);
    } else if (input->type == STDIN_INPUT) {
        display_stdin_input(input, algo, options);
    }
}