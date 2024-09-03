#include <stdlib.h>
#include <string.h>

#include "ft_ssl.h"
#include "ft_md5.h"

int main(int argc, char **argv) {
    ssl_t   ssl = {
        .algo = -1,
        .options = 0,
        .ssl_inputs = NULL
    };

    if (check_args(argc, argv, &ssl) == -1) {
        return 1;
    }

    ssl_input_t *tmp = ssl.ssl_inputs;
    
    #include "utils.h"
    while (tmp) {
        tmp->hash = ft_md5(tmp->ssl_str, tmp->len);
        ft_hexdump(tmp->hash, 16);
        tmp = tmp->next;
    }

    free_ssl_inputs(ssl.ssl_inputs);
    return 0;
}