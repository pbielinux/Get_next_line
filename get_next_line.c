/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:30:14 by pbielik           #+#    #+#             */
/*   Updated: 2021/03/31 22:36:24 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *str, char c, size_t n)
{
	size_t	i;
	char	*s;

	s = (char*)str;
	i = 0;
	while (i < n)
	{
		s[i] = c;
		i++;
	}
	return (s);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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
	if (!(copy = malloc((unsigned int)len)))
		return (NULL);
	ft_memcpy(copy, str, len);
	return (copy);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	if (!(new = (char *)malloc(sizeof(char) *
		(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		str++;
	}
	if ((char)c == '\0')
		return ((char *)str);
	return (NULL);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	min_len;
	char			*sub;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s) || len <= 0)
		return (ft_strdup(""));
	else
	{
		min_len = ft_strlen(&s[start]);
		if (min_len < len)
			len = min_len;
		if (!(sub = malloc(sizeof(char) * len + 1)))
			return (NULL);
		i = start;
		while (s[i] && (i - start) < len)
		{
			sub[i - start] = s[i];
			i++;
		}
		sub[i - start] = '\0';
	}
	return (sub);
}


int	gnl_read_file(int fd, char *heap, char **stack)
{
	char	*tmp_stack;
	int		ret;

	while (!(ft_strchr(stack, '\n')))
	{
		ret = read(fd, heap, BUFFER_SIZE);
		heap[ret] = '\0';
		if (!(stack))
			stack = ft_strdup(heap);
		else
		{
			tmp_stack = stack;
			stack = ft_strjoin(tmp_stack, heap);
		}
		if (stack[0] == '\0' || ret == 0)
			return (0);
	}
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static	char	*stack[FD_SIZE];
	char			*heap;
	char			*tmp;
	int				i;

	stack[fd] = malloc(sizeof(char *) * 2);

	if (read(fd, 0, 0) == -1 || !(heap = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);

	if (gnl_read_file(fd, heap, &stack[fd][0]))
	{
		i = 0;
		while (stack[fd][i])
		{
			if (stack[fd][i] == '\n')
			{
				*line = ft_substr(stack[fd], 0, i);
				tmp = stack[fd];
				stack[fd] = ft_strdup(tmp + i + 1);
				return (1);
			}
			i++;
		}
		return (1);
	}
	else
	{
		if(!(*line = stack[fd]))
			line = "";
		return (0);
	}

}


int main()
{
	int fd;
	char *line;

	fd = open("/Users/pbielik/Desktop/Get_next_line/gnlTester/files/41_with_nl", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);

	return 0;
}

