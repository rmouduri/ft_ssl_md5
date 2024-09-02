#include <stdlib.h>
#include <string.h>

#include "ft_ssl.h"
#include "ft_md5.h"

int main(int argc, char **argv) {
    // ssl_t   ssl = {
    //     .command = 0,
    //     .options = 0,
    //     .ssl_inputs = NULL
    // };

    // if (check_args(argc, argv, &ssl) == false) {
    //     return 1;
    // }

    (void)argc;
    ft_md5((uint8_t *) argv[1], strlen(argv[1]));

    return 0;
}