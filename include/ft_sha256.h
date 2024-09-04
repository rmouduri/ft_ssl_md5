#include <stdint.h>
#include <stddef.h>

#ifndef _FT_SHA256_
# define _FT_SHA256_

// enum sha256_state {
//     A = 0,
//     B = 1,
//     C = 2,
//     D = 3
// };

typedef struct ft_sha256_s {
    uint32_t    state[4];
    uint32_t    *input;
    size_t      input_len;
} ft_sha256_t;


uint8_t *ft_sha256(const uint8_t *input, const size_t input_len);

#endif // _FT_SHA256_