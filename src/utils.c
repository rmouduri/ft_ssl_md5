#include "stddef.h"

void	*ft_memcpy(void *dest, const void *src, size_t n) {
	size_t				i;
	unsigned char		*destcpy;
	const unsigned char	*srccpy;

	destcpy = dest;
	srccpy = src;
	i = -1;
	while (++i < n)
		destcpy[i] = srccpy[i];
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n) {
	size_t			i;
	unsigned char	*scpy;

	scpy = s;
	i = -1;
	while (++i < n)
		scpy[i] = (unsigned char)c;
	return (s);
}

int	ft_strcmp(const char *s1, const char *s2) {
	size_t	i;

	i = 0;
	while ((unsigned char)s1[i] && (unsigned char)s2[i] &&
		(unsigned char)s1[i] == (unsigned char)s2[i])
		++i;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}