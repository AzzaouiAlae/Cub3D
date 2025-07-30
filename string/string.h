/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_string.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:03 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/08 05:36:06 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPP_STRING_H
# define CPP_STRING_H
# include "../garbage_collector/garbage_collector.h"

typedef struct s_str
{
	char	*content;
	int		count;
	int		capacity;
}			t_str;

void		str_resize(t_str *str, int capacity);
void		str_delete_char(t_str *str, int index);
void		str_delete_len(t_str *str, int index, int len);
void		str_insert(t_str *str, char *value, int index);
void		str_insert_char(t_str *str, char value, int index);
void		str_add_len(t_str *str, char *arr, int len);
void		str_add(t_str *str, char *arr);
void		str_add_char(t_str *str, char ch);
t_str	*str_new_capacity(int capacity);
t_str	*str_new(void);
void		str_delete_char(t_str *str, int index);
t_str	*str_new_substitute(char *s);
void		str_clear(t_str *str);

#endif