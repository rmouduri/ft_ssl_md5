#include <stdlib.h>
#include <string.h>

#include "ft_ssl.h"
#include "ft_md5.h"

int main(int argc, char **argv) {
    ssl_t   ssl = {
        .command = 0,
        .options = 0,
        .ssl_inputs = NULL
    };

    if (check_args(argc, argv, &ssl) == false) {
        return 1;
    }

    ft_md5((uint8_t *) argv[2], strlen(argv[2]));

    return 0;
}