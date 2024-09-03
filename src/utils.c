#include <stdio.h>
#include <ctype.h>

void ft_hexdump(const void *ptr, int size) {
    const unsigned char *buffer = (unsigned char *) ptr;
    int i, j;

    for (i = 0; i < size; i += 16) {
        printf("%08x  ", i);

        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                printf("%02x ", buffer[i + j]);
            } else {
                printf("   ");
            }
        }

        printf(" ");

        for (j = 0; j < 16; j++) {
            if (i + j < size) {
                const unsigned char ch = buffer[i + j];
                if (isprint(ch)) {
                    printf("%c", ch);
                } else {
                    printf(".");
                }
            }
        }

        printf("\n");
    }
}

void ft_binarydump(const void *ptr, int size) {
    const unsigned char *buffer = (unsigned char *) ptr;
    int i, j;

    for (i = 0; i < size; i += 8) {
        printf("%08x  ", i);

        for (j = 0; j < 8; j++) {
            if (i + j < size) {
                const unsigned char byte = buffer[i + j];
                for (int bit = 7; bit >= 0; bit--) {
                    printf("%d", (byte >> bit) & 1);
                }
                printf(" ");
            } else {
                printf("         ");
            }
        }

        printf(" ");

        for (j = 0; j < 8; j++) {
            if (i + j < size) {
                const unsigned char ch = buffer[i + j];
                if (isprint(ch)) {
                    printf("%c", ch);
                } else {
                    printf(".");
                }
            }
        }

        printf("\n");
    }
}