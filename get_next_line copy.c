/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line copy.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielinux <pbielinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:30:14 by pbielik           #+#    #+#             */
/*   Updated: 2021/04/09 17:48:46 by pbielinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
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

char	*ft_strcdup(const char *str, char c)
{
	size_t	len;
	char	*copy;

	len = 0;
	while (str[len] != c)
		len++;
	if (!(copy = malloc((unsigned int)len + 1)))
		return (NULL);
	ft_memcpy(copy, str, len);
	copy[len + 1] = '\0';
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
*/

void	gnl_add_clear(char **stack, char **line, int r)
{
	size_t		i;
	char		*tmp_stack;

	i = 0;
	while ((*stack)[i])
	{
		if ((*stack)[i] == '\n')
			break;
		i++;
	}
	if (i < ft_strlen(*stack))
	{
		*line = ft_substr(*stack, 0, i);
		tmp_stack = ft_substr(*stack, i + 1, ft_strlen(*stack));
		free(*stack);
		*stack = ft_strdup(tmp_stack);
		free (tmp_stack);
	}
	else if (r == 0)
	{
		*line = ft_substr(*stack, 0, ft_strlen(*stack));
		if (*stack)
		{
			free(*stack);
			*stack = NULL;
		}
	}
}

// if the EOF was reached in a previous call, gnl_read_file will return 0;
int		gnl_read_file(int fd, char **stack)
{

	char			*buffer; //Heap can stay, ***** Need to be (void *)??? *****
	char			*tmp;
	int				ret;

	buffer = malloc(sizeof(char *) * (BUFFER_SIZE + 1));

	while ((ret = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[ret] = '\0';

		tmp = ft_strjoin(*stack, buffer);
		free(*stack);
		*stack = NULL;
		*stack = tmp;
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free (buffer);
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static	char	*stack[FD_SIZE];
	int				ret;

	if (line == NULL || read(fd, 0, 0) == -1 || BUFFER_SIZE < 0)
		return (-1);

	if (stack[fd] == NULL)
		stack[fd] = calloc(sizeof(char), sizeof(char));

	ret = gnl_read_file(fd, &stack[fd]);

	if (ret == 0)
		*line = ft_strdup(stack[fd]);
	else if
		*line = ft_substr(stack[fd], 0 , ft_strchr(stack[fd], '\n') - stack[fd])

	gnl_add_clear(&stack[fd], line, ret);

	if (ret > 0)
		return (1);
	else
		return (0);
}

/*
int main()
{
	int fd;
	char *line;

	fd = open("/Users/pbielik/Desktop/Get_next_line/41_with_nl", O_RDONLY);
	printf("\nReturn: %d , Line: %s\n", get_next_line(fd, &line), line);
	free(line);
	printf("\nReturn: %d , Line: %s\n", get_next_line(fd, &line), line);
	free(line);
	printf("\nReturn: %d , Line: %s\n", get_next_line(fd, &line), line);
	free(line);


	return 0;
}
*/
