/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_func.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:14 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/09/02 22:59:16 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FUNC_H
# define FT_FUNC_H
# include "../string/string.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
int		ft_strlen(const char *s);
char	*ft_substr(const char *s, int start, int len);
char	**ft_super_split(const char *s, char *sep, char *special_sep);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strslen(char **strs);
int		is_digit(char ch);
int		ft_atoi(const char *str, int *error);
void	ft_putstr_fd(int fd, char *s, int len);
int		ft_open(char *file_name, int flag, int perm);
int		ft_count_char(char *str, char ch);

#endif
