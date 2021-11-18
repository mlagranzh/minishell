/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:23:50 by celys             #+#    #+#             */
/*   Updated: 2021/11/16 01:51:22 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	child_process(t_main *main, int **fd, int i)
{
	close(fd[i][1]);
	main->gap->pipe_in = fd[i];
	main->gap->pipe_out = fd[i + 1];
	execute_pipe(main);
	close(fd[i][0]);
}

static void	start_pipe(int *fd, t_main *main)
{
	main->gap->pipe_in = NULL;
	main->gap->pipe_out = fd;
	execute_pipe(main);
}

static void	end_pipe(int *fd, t_main *main)
{
	main->gap->pipe_in = fd;
	main->gap->pipe_out = NULL;
	execute_pipe(main);
}

static int	**init_fd(int **fd, int count_pipe)
{
	int	i;

	i = 0;
	fd = malloc_int_int(sizeof(int *) * (count_pipe));
	while (i < count_pipe - 1)
	{
		fd[i] = malloc_int(sizeof(int) * 2);
		if (pipe(fd[i]) == -1)
		{
			perror("ERROR PIPE");
			exit(1);
		}
		i++;
	}
	fd[i] = NULL;
	return (fd);
}

void	pipe_work(t_main *main)
{
	int	**fd;
	int	i;

	fd = NULL;
	fd = init_fd(fd, main->pipe);
	if (main->gap->comm != NULL)
		start_pipe(fd[0], main);
	main->gap = main->gap->next;
	i = 0;
	while (++i && main->gap->next != NULL)
	{
		if (main->gap->comm == NULL)
		{
			main->gap = main->gap->next;
			continue ;
		}
		child_process(main, fd, i - 1);
		main->gap = main->gap->next;
	}
	if (main->gap->comm != NULL)
		end_pipe(fd[i - 1], main);
	close(fd[0][0]);
	close(fd[i - 1][1]);
	fd = free_2d_int(fd);
}
