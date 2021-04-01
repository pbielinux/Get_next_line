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

char	*ft_strndup(const char *str, size_t n)
{
	char *copy;

	if (!(copy = (char *)malloc(sizeof(char) * n + 1)))
		return (NULL);
	ft_memcpy(copy, str, n);
	copy[n] = '\0';
	return (copy);
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

int	ft_strcmp(const char *str1, const char *str2)
{
	size_t i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
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



// Change return type to take advantage of that system calls of read behaves like static variables.
// if the EOF was reached in a previous call, gnl_read_file will return 0;
char	*gnl_read_file(int fd)
{
	// Transfer Stack to main to have a way to avoid calling the read if not neeeded
	// (like when stack already holds a newline from previous call)

	static	char	*stack[FD_SIZE]; //Move to main
	char			*heap; //Heap can stay
	char			*tmp_stack;
	char			*tmp2;
	int				ret;
	int 			i;

	if (!stack[fd])
		stack[fd] = malloc(sizeof(char *) * 2);
	heap = malloc(sizeof(char) * (BUFFER_SIZE + 1));

	while (!(ft_strchr(stack[fd], '\n'))) //condition this while in ret > 0
	{
		ret = read(fd, heap, BUFFER_SIZE);
		heap[ret] = '\0';
		if (!(stack[fd]))
			stack[fd] = ft_strdup(heap);
		else
		{
			tmp_stack = stack[fd];
			stack[fd] = ft_strjoin(tmp_stack, heap);
		}
		if (stack[fd] == '\0')
			return ("");
		if (ret == 0) //this break have to be called if ret == 0 || stack already had a \n f the stack
			break;
	}


	/* Create a function for this purpose and call at main */
	// Clear the Stack before return //
	i = 0;
	while (stack[fd][i] != '\n')
		i++;
	tmp2 = ft_strdup(&(stack[fd][i + 1]));
	stack[fd] = tmp2;
	free (tmp2);
	if (ret == 0 && !(ft_strcmp(stack[fd], tmp_stack)))
		return (NULL);
	return (tmp_stack);
}

int		get_next_line(int fd, char **line)
{

	if (read(fd, 0, 0) == -1)
		return (-1);

	//if stack have something, check if has a \n, if not call read
	ret = gnl_read_file(fd);

	//if ret == 0 && stack have something -> line becomes stack

	//line becomes stack until the \n
	//clear the char after \n from stack
	//return (1)

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
	get_next_line(fd, &line);
	printf("%s\n", line);

	return 0;
}

