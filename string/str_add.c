/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpp_str_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:22:48 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/06 22:22:49 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

void	str_add_char(t_str *str, char ch)
{
	if (!str)
		return ;
	if (str->capacity - 1 == str->count)
		str_resize(str, str->capacity * 2);
	str->content[str->count] = ch;
	(str->count)++;
}

void	str_add(t_str *str, char *arr)
{
	int	i;

	if (!str || !arr || !arr[0])
		return ;
	i = 0;
	while (arr[i])
	{
		str_add_char(str, arr[i]);
		i++;
	}
}

void	str_add_len(t_str *str, char *arr, int len)
{
	int	i;

	if (!str || !arr || !arr[0])
		return ;
	i = 0;
	while (arr[i] && len > i)
	{
		str_add_char(str, arr[i]);
		i++;
	}
}
