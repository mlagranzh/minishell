/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:40:47 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 21:25:33 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void fortytwo()

int	args(t_gap *gap, char *str, int i, int last_pos)
{
	char	*tmp1;

	tmp1 = ft_substr(str, last_pos, i - last_pos);
	if (!(gap->arg))
	{
		gap->arg = (char **)malloc(sizeof(char *) + 1);
		if (!gap->arg)
			return (E_MALLOC);
		gap->arg[0] = tmp1;
		gap->arg[1] = NULL;
		return (NOT_ERROR);
	}
	gap->arg = ft_sstrjoin(gap->arg, tmp1);
	if (!gap->arg)
		return (E_MALLOC);
	return (NOT_ERROR);
}
