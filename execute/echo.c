/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:21:53 by celys             #+#    #+#             */
/*   Updated: 2021/11/16 01:30:01 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_flag(char *string)
{
	if (string == NULL)
		return (0);
	else if (*string != '-')
		return (0);
	string++;
	if (*string == '\0')
		return (0);
	while (*string != '\0')
	{
		if (*string == 'n')
			string++;
		else
			return (0);
	}
	return (1);
}

int	echo(t_main *main)
{
	size_t	i;
	int		flag;

	i = 0;
	flag = 0;
	if (check_flag(main->gap->arg[i]))
	{
		while (check_flag(main->gap->arg[i]))
			i++;
		flag = 1;
	}
	while (main->gap->arg[i] != NULL)
	{
		ft_putstr_fd(main->gap->arg[(i++)], main->gap->fd_out);
		if (main->gap->arg[i] != NULL)
			ft_putstr_fd(" ", main->gap->fd_out);
	}
	if (!flag)
		ft_putstr_fd("\n", main->gap->fd_out);
	exit_exec(main, 0);
	return (1);
}
