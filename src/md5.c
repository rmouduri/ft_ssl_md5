#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "ft_ssl.h"
#include "ft_md5.h"


static bool MD5_Padding(const uint8_t *input, const size_t input_len, ft_md5_t *md5) {
    uint8_t *padded_input;

    md5->input_len = 64 + (64 * ((input_len / 64) + (input_len % 64 >= 56 ? 1 : 0)));
    padded_input = malloc(sizeof(uint8_t) * md5->input_len);

    if (padded_input == NULL) {
        print_malloc_error("MD5_Padding");
        return false;
    }

    memcpy(padded_input, input, input_len);
    memset(padded_input + input_len, 0b10000000, 1);
    memset(padded_input + input_len + 1, 0, md5->input_len - (input_len + 1));

    const uint64_t input_len_to_display = input_len * 8;
    memcpy(padded_input + (md5->input_len - 8), &input_len_to_display, sizeof(uint64_t));

    md5->input = (uint32_t *) padded_input;
    return true;
}

static uint32_t combine(uint32_t state[4], uint32_t input, uint8_t i, uint32_t k, uint32_t rot) {
    uint32_t ans = 0;

    if (i < 16) {
        ans = state[A] + F(state[B], state[C], state[D]) + input;
    } else if (i < 32) {
        ans = state[A] + G(state[B], state[C], state[D]) + input;
    } else if (i < 48) {
        ans = state[A] + H(state[B], state[C], state[D]) + input;
    } else if (i < 64) {
        ans = state[A] + I(state[B], state[C], state[D]) + input;
    }

    ans += k;
    ans = ROTATE_LEFT(ans, rot);
    ans += state[B];

    return ans;
}

static void MD5_Algo(ft_md5_t *md5) {
    const uint32_t k[64] = K;
    const uint32_t r[64] = R;
    uint32_t tmp_state[4];
    uint32_t combine_res = 0;
    uint8_t g;

    for (uint8_t i = 0; i < md5->input_len; i += 64) {
        tmp_state[A] = md5->state[A];
        tmp_state[B] = md5->state[B];
        tmp_state[C] = md5->state[C];
        tmp_state[D] = md5->state[D];

        for (uint8_t j = 0; j < 64; ++j) {
            if (j < 16) {
                g = j;
            } else if (j < 32) {
                g = ((j * 5 + 1) % 16);
            } else if (j < 48) {
                g = ((j * 3 + 5) % 16);
            } else if (j < 64) {
                g = ((j * 7) % 16);
            }

            combine_res = combine(tmp_state, md5->input[(i / 4) + g], j, k[j], r[j]);
            tmp_state[A] = tmp_state[D];
            tmp_state[D] = tmp_state[C];
            tmp_state[C] = tmp_state[B];
            tmp_state[B] = combine_res;
        }

        md5->state[A] += tmp_state[A];
        md5->state[B] += tmp_state[B];
        md5->state[C] += tmp_state[C];
        md5->state[D] += tmp_state[D];
    }
}

uint8_t *ft_md5(const uint8_t *input, const size_t input_len) {
    ft_md5_t    md5;
    uint8_t    *ans;

    md5.state[A] = 0x67452301;
    md5.state[B] = 0xEFCDAB89;
    md5.state[C] = 0x98BADCFE;
    md5.state[D] = 0x10325476;

    if (MD5_Padding(input, input_len, &md5) == false) {
        return NULL;
    }

    MD5_Algo(&md5);

    free(md5.input);

    if ((ans = malloc(sizeof(uint8_t) * 16)) == NULL) {
        print_malloc_error("ft_md5");
        return NULL;
    }

    memcpy(ans, md5.state, sizeof(md5.state));
    return ans;
}