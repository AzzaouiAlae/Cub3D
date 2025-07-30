/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aazzaoui <aazzaoui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:09:36 by aazzaoui          #+#    #+#             */
/*   Updated: 2025/01/29 12:45:30 by aazzaoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "garbage_collector.h"

void	ft_bzero(void *mem, size_t size)
{
	char	*s;
	size_t	i;

	if (!mem)
		return ;
	s = (char *)mem;
	i = 0;
	while (i < size)
	{
		*s = '\0';
		s++;
		i++;
	}
}

void	*ft_calloc_without_save(size_t n, size_t type_size)
{
	void	*mem;
	size_t	full_size;

	full_size = n * type_size;
	mem = malloc(full_size);
	if (!mem)
	{
		perror("Error memory allocation");
		ft_exit(1);
		return (NULL);
	}
	ft_bzero(mem, full_size);
	return (mem);
}

void	*ft_calloc(size_t n, size_t type_size)
{
	void	*mem;

	mem = ft_calloc_without_save(n, type_size);
	save_mem(mem);
	return (mem);
}
