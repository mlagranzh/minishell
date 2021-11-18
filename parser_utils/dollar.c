/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:42:04 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 19:45:16 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*it_is_question_mark(char *str, int *i, int status)
{
	t_tmps	tmps;

	tmps.tmp1 = ft_substr(str, 0, *i);
	tmps.tmp2 = ft_itoa(status);
	tmps.tmp3 = ft_strdup(str + *i + 2);
	tmps.tmp4 = ft_strjoin(tmps.tmp1, tmps.tmp2);
	free(str);
	if (!tmps.tmp4)
		return (free_tmps(tmps));
	*i = ft_strlen(tmps.tmp4);
	free(tmps.tmp1);
	tmps.tmp1 = ft_strjoin(tmps.tmp4, tmps.tmp3);
	if (!tmps.tmp1)
		return (free_tmps(tmps));
	free(tmps.tmp2);
	free(tmps.tmp3);
	free(tmps.tmp4);
	return (tmps.tmp1);
}

static char	*empty_key(t_tmps tmps, int *i, int j)
{
	tmps.tmp2 = ft_strjoin(tmps.tmp1, tmps.tmp3);
	if (!tmps.tmp2)
		return (free_tmps(tmps));
	free(tmps.tmp1);
	free(tmps.tmp3);
	*i = j;
	return (tmps.tmp2);
}

static t_tmps	write_tmps(char *str, int *i, int j)
{
	t_tmps	tmps;

	tmps.tmp1 = ft_substr(str, 0, j);
	tmps.tmp2 = ft_substr(str, j + 1, *i - j - 1);
	tmps.tmp3 = ft_strdup(str + *i);
	tmps.tmp4 = NULL;
	return (tmps);
}

static char	*dollar2(char *str, int *i, int j, char **envp)
{
	t_tmps	tmps;
	char	*envp_key;
	int		keylen;

	tmps = write_tmps(str, i, j);
	keylen = ft_strlen(tmps.tmp2);
	if (keylen == 0)
	{
		free_tmps(tmps);
		return (str);
	}
	free (str);
	tmps.tmp4 = envp_search(tmps.tmp2, envp, keylen);
	free (tmps.tmp2);
	if (!tmps.tmp4)
		return (empty_key(tmps, i, j));
	envp_key = ft_strchr(tmps.tmp4, tmps.tmp4[keylen + 1]);
	tmps.tmp2 = ft_strjoin(tmps.tmp1, envp_key);
	free(tmps.tmp4);
	*i = ft_strlen(tmps.tmp2);
	free(tmps.tmp1);
	tmps.tmp1 = ft_strjoin(tmps.tmp2, tmps.tmp3);
	free(tmps.tmp2);
	free(tmps.tmp3);
	return (tmps.tmp1);
}

char	*dollar(char *str, int *i, char **envp, int status)
{
	int	j;

	j = *i;
	if (ft_isdigit(str[*i + 1]))
		return (it_is_digit(str, i, j));
	if (str[*i + 1] == '?')
		return (it_is_question_mark(str, i, status));
	while (str[++(*i)])
		if (!ft_iskey(str[*i]))
			break ;
	if (*i == j + 1)
		return (str);
	return (dollar2(str, i, j, envp));
}
