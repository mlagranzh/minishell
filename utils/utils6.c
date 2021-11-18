/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 01:02:28 by celys             #+#    #+#             */
/*   Updated: 2021/11/16 01:53:31 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	**free_2d_int(int **array)
{
	size_t	i;

	i = 0;
	if (array == NULL)
		return (NULL);
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	my_free(char *string)
{
	if (string)
		free(string);
}

int	free_ret(t_tmps *tmps, int ret)
{
	if (tmps->tmp1)
		free(tmps->tmp1);
	tmps->tmp1 = NULL;
	if (tmps->tmp2)
		free(tmps->tmp2);
	tmps->tmp2 = NULL;
	if (tmps->tmp3)
		free(tmps->tmp3);
	tmps->tmp3 = NULL;
	if (tmps->tmp4)
		free(tmps->tmp4);
	tmps->tmp4 = NULL;
	if (tmps->tmp5)
		free_2d_array(tmps->tmp5);
	tmps->tmp5 = NULL;
	free(tmps);
	return (ret);
}

char	**ft_realloc(char **old, size_t size)
{
	char	**new;
	size_t	i;

	i = 0;
	new = malloc_ch_ch(size);
	while (i < len_2d_array(old))
	{
		new[i] = ft_strdup(old[i]);
		i++;
	}
	new[i++] = NULL;
	new[i] = NULL;
	old = free_2d_array(old);
	return (new);
}

char	**free_2d_array(char **p)
{
	size_t	i;

	if (p == NULL)
		return (p);
	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
	return (NULL);
}
