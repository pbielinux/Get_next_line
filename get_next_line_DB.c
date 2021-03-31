/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_DB.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:30:14 by pbielik           #+#    #+#             */
/*   Updated: 2021/03/30 19:21:54 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define FD_SIZE 4096
# define BUFFER_SIZE 8

int	get_next_line(int fd, char **line);
size_t	ft_strlen(const char *str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);

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

int ft_get_line(char **s, char **line)
{
	int len;
	char *tmp;

		len  = 0;
		while ((*s)[len] != '\n' && (*s)[len] != '\0')
			len++;
		if ((*s)[len] == '\n')
		{
			*line = ft_substr((*s), 0, len);
			tmp = ft_strdup(&((*s)[len + 1]));
			free(*s);
			(*s) = tmp;
		}
		else
		{
			*line = ft_strdup(*s);
			free (*s);
			(*s) = NULL;
		}
		return (1);
}

int	get_next_line(int fd, char **line)
{
	int ret;
	static char *s[FD_SIZE];
	char buffer[BUFFER_SIZE + 1];
	char *temp;

	if (line == NULL || read(fd, 0, 0) == -1)
		return (-1);

	while ((ret = read (fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buffer);
		else
		{
			temp = ft_strjoin(s[fd], buffer);
			free (s[fd]);
			s[fd] = temp;
 		}
		if (ft_strchr(s[fd], '\n'))
			break;
	}

	if (ret < 0)
		return (-1);
	else if (ret == 0 || s[fd] == NULL)
		return (0);
	else
		return (ft_get_line(&s[fd], line));
}

 int main()
{
	int fd;
	char *line;

	fd = open("/Users/pbielik/Desktop/Get_next_line/gnlTester/files/empty", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);

	return 0;
}

