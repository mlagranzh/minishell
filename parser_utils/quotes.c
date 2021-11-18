/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:45:01 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 18:45:02 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*util(char *str, int *i, int j)
{
	t_tmps	tmps;

	tmps.tmp1 = ft_substr(str, 0, j);
	tmps.tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmps.tmp3 = ft_strdup(str + *i + 1);
	free(str);
	tmps.tmp4 = ft_strjoin(tmps.tmp1, tmps.tmp2);
	if (!tmps.tmp4)
		return (free_tmps(tmps));
	free(tmps.tmp1);
	free(tmps.tmp2);
	tmps.tmp1 = ft_strjoin(tmps.tmp4, tmps.tmp3);
	if (!tmps.tmp1)
		return (free_tmps(tmps));
	free(tmps.tmp4);
	free(tmps.tmp3);
	*i -= 1;
	return (tmps.tmp1);
}

char	*quotes1(char *str, int *i)
{
	int	j;

	j = *i;
	while (str[++(*i)])
		if (str[*i] == '\'')
			break ;
	return (util(str, i, j));
}

char	*quotes2(char *str, int *i, char **envp, int status)
{
	int	j;

	j = (*i)++;
	while (str[*i])
	{
		if (*(str + *i) == '$')
		{
			str = dollar(str, i, envp, status);
			if (!str)
				return (NULL);
		}
		else if (str[*i] == '\"')
			break ;
		else
			(*i)++;
	}
	return (util(str, i, j));
}
