#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# define FD_SIZE 4096

size_t	ft_strlen(const char *str);
void	ft_memdel(void **ptr);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *str);
char	*ft_join(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(const char *s, unsigned int start, size_t len);
int		get_line(char *str, char **line);
int		get_next_line(int fd, char **line);

#endif
