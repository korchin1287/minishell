/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ndreadno <ndreadno@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 13:28:21 by ndreadno          #+#    #+#             */
/*   Updated: 2020/10/04 14:02:01 by ndreadno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	char *content;
	struct s_list *next;
}				t_list;
char		g_buf[2];

int		ft_tolower(int ch);
int		ft_toupper(int ch);
int		ft_isalnum(int ch);
int		ft_isalpha(int ch);
int		ft_isascii(int ch);
int		ft_isdigit(int ch);
int		ft_isprint(int ch);
int		ft_strcmp(char *s1, char *s2);
int		ft_space(char *str, int i);
int		ft_skip_digit(char *str, int i);
int		ft_atoi(const char *str);
int     ft_lstsize(t_list *lst);
int		ft_get_next_line(int fd, char **line);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	**ft_split(char const *s, char c);
char	**ft_two_ar_dup(char **str);
char	*ft_strchr(const char *str, int ch);
char	*ft_strrchr(const char *str, int ch);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim_char(char *str, char trim, int size);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_bzero(char *s, int n);
void	ft_free_null(void **var);
void	ft_putnbr_fd(int n, int fd);
void	*ft_malloc(size_t type_size, size_t size);
void	ft_putendl_fd(char *s, int fd);
void	*ft_calloc(size_t num, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
void	*ft_memset(void *destination, int c, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	ft_strcpy(char *dst, char *src);
void            ft_lstadd_front(t_list **lst, t_list *new);
void            ft_lstadd_back(t_list **lst, t_list *new);
void            ft_lstdelone(t_list *lst, void (*del)(void*));
void            ft_lstclear(t_list **lst, void (*del)(void*));
void            ft_lstiter(t_list *lst, void (*f)(void*));
t_list      *ft_lstnew(void *content);
t_list            *ft_lstlast(t_list *lst);
t_list            *ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*));
size_t	ft_strlen(const char *str);
size_t	ft_strlen_3(const char *str, char c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
