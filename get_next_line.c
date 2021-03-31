/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:30:14 by pbielik           #+#    #+#             */
/*   Updated: 2021/03/31 15:32:28 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_verify_line(char **stack, char **line)
{
	char *tmp_stack;
	char *strchr_stack;
	int i;

	i = 0;
	strchr_stack = *stack;
	while (strchr_stack[i] != '\n')
		if (!(strchr_stack[i++]))
			return (0);
	tmp_stack = &(strchr_stack[i]);
	*tmp_stack = '\0';
	*line = ft_strdup(*stack);
	*stack = ft_strdup(tmp_stack + 1);

	return (1);
}

int gnl_read_file(int fd, char *heap, char **stack, char **line)
{
	int ret;
	char *tmp_stack;

	while ((ret = read (fd, heap, BUFFER_SIZE)) > 0)
		{
			heap[ret] = '\0';
			if (*stack)
			{
				tmp_stack = *stack;
				*stack = ft_strjoin(tmp_stack, heap);
				free(tmp_stack);
				tmp_stack = NULL;
			}
			else
				*stack = ft_strdup(heap);
			if (gnl_verify_line(stack, line))
				break;
		}
		return (ret > 0 ? 1 : 0);
}

int	get_next_line(int fd, char **line)
{
	static	char	*stack[FD_SIZE];
	char			*heap;
	int				ret;
	int				i;

	if (line == NULL || (read(fd, 0, 0) == -1) \
		|| !(heap = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);

	if (stack[fd])
		if (gnl_verify_line(&stack[fd], line))
			return (1);

	ft_memset(heap, '\0', BUFFER_SIZE);

	ret = gnl_read_file(fd, heap, &stack[fd], line);
	free(heap);

	if (ret != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ret && *line)
			*line = NULL;
		return (ret);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (1);
}

/* int main()
{
	int fd;
	char *line;

	fd = open("/Users/pbielik/Desktop/Get_next_line/test.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);

	return 0;
}
*/
