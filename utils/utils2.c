/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:07:07 by celys             #+#    #+#             */
/*   Updated: 2021/11/17 11:51:20 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	len_2d_array(char **string)
{
	size_t	i;

	i = 0;
	if (string == NULL)
		return (0);
	while (string[i] != NULL)
		i++;
	return (i);
}

char	**array_2d_dup(char **array)
{
	char	**duplicate;
	size_t	i;

	i = 0;
	duplicate = malloc_ch_ch(sizeof(char *) * (len_2d_array(array) + 2));
	while (i < len_2d_array(array))
	{
		duplicate[i] = ft_strdup(array[i]);
		i++;
	}
	duplicate[i] = NULL;
	return (duplicate);
}

t_gap	*initial_gap(void)
{
	t_gap	*gap;

	gap = (t_gap *)malloc(sizeof(t_gap));
	if (!gap)
		return (NULL);
	gap->comm = NULL;
	gap->next = NULL;
	gap->fd_in = 0;
	gap->fd_out = 1;
	gap->redir_flag = R_FALSE;
	gap->if_arg = FALSE;
	gap->first_arg = NULL;
	gap->syntax_flag = TRUE;
	gap->arg = (char **)malloc(sizeof(char *));
	if (!gap->arg)
	{
		free (gap);
		return (NULL);
	}
	gap->arg[0] = NULL;
	return (gap);
}

char	**sort_dictionary(char **dictionary)
{
	size_t	i;
	int		not_sorted;
	char	**new_array;
	char	*tmp;

	new_array = array_2d_dup(dictionary);
	not_sorted = 1;
	i = 0;
	while (not_sorted)
	{
		not_sorted = 0;
		i = -1;
		while (++i < len_2d_array(dictionary) - 1)
		{
			if (ft_strncmp(new_array[i], new_array[i + 1], \
					ft_strlen(new_array[i])) > 0)
			{
				tmp = new_array[i];
				new_array[i] = new_array[i + 1];
				new_array[i + 1] = tmp;
				not_sorted = 1;
			}
		}
	}
	return (new_array);
}
