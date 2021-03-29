/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbielik <pbielik@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 19:30:14 by pbielik           #+#    #+#             */
/*   Updated: 2021/03/29 23:09:55 by pbielik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_next_line(int fd, char **line)
{
	int ret;
	static char *s[FD_SIZE];
	char buffer[BUFFER_SIZE + 1];
	char *temp;

	if (fd < 0 || line == NULL)
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
	else if (ret == 0 && s[fd] == NULL)
		return (0);
	else
	{
		int len;
		char *tmp;

		len  = 0;
		while (s[fd][len] != '\n' && s[fd][len] != '\0')
			len++;
		if (s[fd][len] == '\n')
		{
			*line = ft_substr(s[fd], 0, len);
			tmp = ft_strdup(&(s[fd][len + 1]));
			free(s[fd]);
			s[fd] = tmp;
		}
		else
		{
			*line = ft_strdup(&(*s[fd]));
			free (s[fd]);
			s[fd] = NULL;
		}
		return (1);
	}
}

/* int main()
{
	int fd;
	char *line;

	fd = open("test.txt", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s\n", line);
	get_next_line(fd, &line);
	printf("%s\n", line);

	return 0;
}
*/
