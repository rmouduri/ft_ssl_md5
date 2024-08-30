#include <stdlib.h>

#include "ft_ssl.h"

int main(int argc, char **argv) {
    ssl_t   ssl = {
        .command = 0,
        .options = 0,
        .ssl_strs = NULL
    };

    if (check_args(argc, argv, &ssl) == false) {
        return 1;
    }

    return 0;
}