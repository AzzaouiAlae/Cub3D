/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabouriz <aabouriz@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:14 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 18:26:06 by aabouriz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FUNC_H
# define FT_FUNC_H
# include "../string/string.h"
# include <fcntl.h>
# include <stdlib.h>
#include <unistd.h>

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
char	*ft_substr(const char *s, int start, int len);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strnstr(char *haystack, char *needle, int len);
char	**ft_super_split(const char *s, char *sep, char *special_sep);
char	*ft_strldup(const char *s1, size_t len);
size_t	ft_strchrlen(const char *s, char ch);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlen_delimiter(const char *s, char *sep);
char	*str_find_char(const char *s, char *sep);
t_str	*ft_itoa(int num);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strslen(char **strs);
int		is_alpha(char ch);
int		is_digit(char ch);
int		ft_atoi(const char *str, int *error);
char	*ft_strrchr(const char *s, int c);
void	ft_putstr_fd(int fd, char *s, int len);
void	ft_close(int fd);
int		ft_open(char *file_name, int flag, int perm);
int		ft_count_char(char *str, char ch);

#endif
