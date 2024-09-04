#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ft_ssl.h"
#include "ft_sha256.h"


uint8_t *ft_sha256(const uint8_t *input, const size_t input_len) {
    // ft_sha256_t    sha256;
    uint8_t    *hash = 0;

    (void) input;
    (void) input_len;
    // if (SHA256_Padding(input, input_len, &sha256) == -1) {
    //     return NULL;
    // }

    // SHA256_Algo(&sha256);

    // free(sha256.input);

    // if ((hash = malloc(sizeof(uint8_t) * 16)) == NULL) {
    //     print_malloc_error("ft_sha256");
    //     return NULL;
    // }

    // memcpy(hash, sha256.state, sizeof(sha256.state));
    return hash;
}