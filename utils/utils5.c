/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:15:50 by celys             #+#    #+#             */
/*   Updated: 2021/11/16 01:49:23 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*malloc_ch(size_t size)
{
	char	*p;

	p = malloc(size);
	if (p == NULL)
		exit(1);
	return (p);
}

char	**malloc_ch_ch(size_t size)
{
	char	**p;

	p = malloc(size);
	if (p == NULL)
		exit(1);
	return (p);
}

int	**malloc_int_int(size_t size)
{
	int	**p;

	p = malloc(size);
	if (p == NULL)
		exit(1);
	return (p);
}

int	*malloc_int(size_t size)
{
	int	*p;

	p = malloc(size);
	if (p == NULL)
		exit(1);
	return (p);
}
