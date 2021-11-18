/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:43:24 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 19:43:25 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_iskey(char c)
{
	if (c == '_' || ft_isalnum(c))
		return (1);
	return (0);
}

char	*envp_search(char *tmp2, char **envp, int keylen)
{
	int	k;

	k = -1;
	while (envp[++k])
		if (ft_strnstr(envp[k], tmp2, keylen) == envp[k]
			&& envp[k][keylen] == '=')
			break ;
	if (envp[k] == NULL)
		return (NULL);
	return (ft_strdup(envp[k]));
}

char	*it_is_digit(char *str, int *i, int j)
{
	t_tmps	tmps;

	tmps.tmp1 = ft_substr(str, 0, j);
	tmps.tmp2 = ft_strdup(str + *i + 2);
	tmps.tmp3 = ft_strjoin(tmps.tmp1, tmps.tmp2);
	tmps.tmp4 = NULL;
	free(str);
	if (!tmps.tmp3)
		return (free_tmps(tmps));
	free(tmps.tmp1);
	free(tmps.tmp2);
	*i = j;
	return (tmps.tmp3);
}
