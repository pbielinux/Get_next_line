/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielinux <pbielinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:30:14 by pbielik           #+#    #+#             */
/*   Updated: 2021/04/12 11:41:48 by pbielinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*ft_join(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*new;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	new = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = -1;
	while (s1[++i])
		new[i] = s1[i];
	ft_memdel((void **)&s1);
	i = -1;
	while (s2[++i])
		new[len1 + i] = s2[i];
	new[len1 + i] = '\0';
	return (new);
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
		sub = malloc(sizeof(char) * len + 1);
		if (sub == NULL)
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

int	get_line(char *str, char **line)
{
	int		i;
	int		len;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	*line = ft_substr(str, 0, i);
	i++;
	len = ft_strlen(str + i) + 1;
	ft_memmove(str, str + i, len);
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char	*stack[FD_SIZE];
	char		buff[BUFFER_SIZE + 1];
	int			ret;

	if (line == NULL || read(fd, 0, 0) == -1 || BUFFER_SIZE < 0)
		return (-1);
	if (stack[fd] && ft_strchr(stack[fd], '\n'))
		return (get_line(stack[fd], line));
	ret = 1;
	while (ret > 0)
	{
		ret = read(fd, buff, BUFFER_SIZE);
		buff[ret] = '\0';
		stack[fd] = ft_join(stack[fd], buff);
		if (ft_strchr(stack[fd], '\n'))
			return (get_line(stack[fd], line));
	}
	if (stack[fd])
	{
		*line = ft_strdup(stack[fd]);
		ft_memdel((void **)&stack[fd]);
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}
