/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_symbol.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:41:40 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 22:02:38 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	control_symbol(t_main *main, char **str, int *i, int *j)
{
	int	flag;

	flag = FALSE;
	if ((str[0][*i] == ' ' || str[0][*i] == '	') && (*i == *j))
		*j = ft_trim_empty(*str, i);
	if (str[0][*i] == '\'' || str[0][*i] == '\"')
		flag = TRUE;
	if (str[0][*i] == '\'')
		*str = quotes1(*str, i);
	else if (str[0][*i] == '\"')
		*str = quotes2(*str, i, main->envp, main->last_exit_status);
	else if (str[0][*i] == '$')
		*str = dollar(*str, i, main->envp, main->last_exit_status);
	if (!(*str))
		main->exit_status = E_MALLOC;
	return (flag);
}
