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
*/

void	gnl_clear_stack(char **stack)
{
	int		i;
	char	*tmp_stack;

	i = 0;
	while ((*stack)[i] != '\n')
		i++;
	tmp_stack = ft_strdup(*stack + i + 1);
	*stack = ft_strdup(tmp_stack);

}

// if the EOF was reached in a previous call, gnl_read_file will return 0;
int		gnl_read_file(int fd, char **stack)
{

	char			*heap; //Heap can stay, ***** Need to be (void *)??? *****
	char			*tmp_stack;
	int				ret;

	heap = malloc(sizeof(char) * (BUFFER_SIZE + 1));

	while ((ret = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[ret] = '\0';
		if (!(*stack))
			*stack = ft_strdup(heap);
		else
		{
			tmp_stack = *stack;
			*stack = ft_strjoin(tmp_stack, heap);
		}
		if (ft_strchr(*stack, '\n') || ret < BUFFER_SIZE)
			break;
	}

	free (heap);
	heap = NULL;

	return (ret > 0 ? 1 : 0);
}

int		get_next_line(int fd, char **line)
{
	static	char	*stack[FD_SIZE];
	int				ret;

	if (read(fd, 0, 0) == -1)
		return (-1);

	ret = gnl_read_file(fd, &stack[fd]);

	if (ret == 0)
	{
		if (stack[fd])
		{
				*line = stack[fd];
				free (stack[fd]);
				stack[fd] = NULL;
		}
		else
			*line = ft_strdup("");
		return (0);
	}

	if (ft_strchr(stack[fd], '\n'))
	{
		*line = ft_strcdup(stack[fd], '\n');
		if(*(line[0]) == '\n')
		{
			*line=ft_strdup("");
		}
		//printf("\n %s \n", *line);
		gnl_clear_stack(&(stack[fd]));
		return (1);
	}
	//if ret == 0 && stack have something -> line becomes stack


	return 0;
}
/*
int main()
{
	int fd;
	char *line;

	fd = open("/Users/pbielik/Desktop/Get_next_line/nl", O_RDONLY);
	printf("\nReturn: %d , Line: %s\n", get_next_line(fd, &line), line);
	free(line);
	printf("\nReturn: %d , Line: %s\n", get_next_line(fd, &line), line);
	if (line)
		free(line);
	printf("\nReturn: %d , Line: %s\n", get_next_line(fd, &line), line);
	free(line);


	return 0;
}
*/
