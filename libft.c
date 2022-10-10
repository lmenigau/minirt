#include <stddef.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

size_t ft_strlen(char *s)
{
	size_t len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
