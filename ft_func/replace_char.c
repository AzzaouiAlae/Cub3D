/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oel-bann <oel-bann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 22:23:37 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/05/09 16:18:40 by oel-bann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_func.h"

char	*replace_char(char *s, char ch, char ch_to_replace)
{
	int		i;
	char	flag;

	i = 0;
	flag = '\0';
	while (s && s[i])
	{
		if (!flag && ft_strchr("'\"", s[i]))
			flag = s[i];
		else if (flag == s[i])
			flag = '\0';
		else if (!flag && s[i] == ch)
			s[i] = ch_to_replace;
		i++;
	}
	return (s);
}
