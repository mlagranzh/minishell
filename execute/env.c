/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:21:53 by celys             #+#    #+#             */
/*   Updated: 2021/11/16 01:30:12 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env(t_main *main)
{
	int	i;

	i = 0;
	while (main->envp[i] != NULL)
	{
		ft_putendl_fd(main->envp[i], main->gap->fd_out);
		i++;
	}
	exit_exec(main, 0);
	return (1);
}
