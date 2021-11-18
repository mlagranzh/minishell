/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:21:53 by celys             #+#    #+#             */
/*   Updated: 2021/11/17 02:07:28 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pwd(t_main *main)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir == NULL)
	{
		print_error(main, errno);
		exit(1);
	}
	ft_putendl_fd(dir, main->gap->fd_out);
	free(dir);
	exit_exec(main, 0);
	return (1);
}
