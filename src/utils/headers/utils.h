#ifndef UTILS_H
# define UTILS_H

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_strcpy(char *s1);

void	free_all(void **ptrs, size_t ptrs_len);

void	*free_return(void **ptrs, size_t ptrs_len, void *value);

int		free_return_int(void **ptrs, size_t ptrs_len, int value);

#endif