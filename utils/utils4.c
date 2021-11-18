/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:08:50 by celys             #+#    #+#             */
/*   Updated: 2021/11/18 14:10:53 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*my_strjoin(char *s1, char *s2, char *s3)
{
	char	*p;
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	p = ft_strjoin(tmp, s3);
	free(tmp);
	return (p);
}

int	i_strchr(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

void	wait_pid(t_main *main)
{
	int	i;

	i = 0;
	while (main->pid[i] != -1)
	{
		if (waitpid(main->pid[i], &main->exit_status, 0) == -1)
			perror("WAIT_PID");
		if (WIFSIGNALED(main->exit_status))
			main->exit_status = 130;
		else
			main->exit_status = WEXITSTATUS(main->exit_status);
		i++;
	}
}

void	add_pid(pid_t *pid, pid_t pid_value)
{
	int	i;

	i = 0;
	while (pid[i] != -1)
		i++;
	pid[i] = pid_value;
}

void	init_pid(t_main *main)
{
	int	i;

	i = 0;
	main->pid = malloc_int((main->pipe + 1) * sizeof(pid_t));
	while (i <= main->pipe)
	{
		main->pid[i] = -1;
		i++;
	}
}
