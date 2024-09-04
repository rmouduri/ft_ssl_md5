#include <stdlib.h>
#include <string.h>

#include "ft_ssl.h"
#include "display.h"
#include "ft_md5.h"
#include "ft_sha256.h"

int main(int argc, char **argv) {
    ssl_t   ssl = {
        .algo = -1,
        .options = 0,
        .ssl_inputs = NULL
    };

    if (check_args(argc, argv, &ssl) == -1) {
        return 1;
    }

    uint8_t *(*hash_fun_ptr[2])(const uint8_t *, const size_t) = {
        &ft_md5,
        &ft_sha256
    };

    ssl_input_t *tmp = ssl.ssl_inputs;
    while (tmp) {
        if (tmp->ssl_str || (!tmp->ssl_str && !tmp->len)) {
            tmp->hash = hash_fun_ptr[ssl.algo](tmp->ssl_str, tmp->len);
        }

        display(tmp, ssl.algo, ssl.options);
        tmp = tmp->next;
    }

    free_ssl_inputs(ssl.ssl_inputs);
    return 0;
}