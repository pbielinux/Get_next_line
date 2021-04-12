#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_memdel(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*cdest;
	const char	*csrc;

	cdest = (char *)dest;
	csrc = (const char *)src;
	if (dest <= src)
		return (ft_memcpy(cdest, csrc, n));
	else
	{
		cdest += n;
		csrc += n;
		while (n--)
		{
			*--cdest = *--csrc;
		}
	}
	return (dest);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*csrc;
	char	*cdest;

	csrc = (char *)src;
	cdest = (char *)dest;
	if (!csrc && !cdest && n > 0)
		return (NULL);
	i = 0;
	while (i < n)
	{
		cdest[i] = csrc[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *str)
{
	size_t	len;
	char	*copy;

	len = ft_strlen(str) + 1;
	copy = malloc((unsigned int)len);
	if (!copy)
		return (NULL);
	ft_memcpy(copy, str, len);
	return (copy);
}
