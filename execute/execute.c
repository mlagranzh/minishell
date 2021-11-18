/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:22:23 by celys             #+#    #+#             */
/*   Updated: 2021/11/18 15:19:06 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redir_pipe(t_main *main)
{
	if (main->pipe > 1)
	{
		if (main->gap->pipe_in != NULL)
		{
			if (main->gap->fd_in == 0)
				if (dup2(main->gap->pipe_in[0], STDIN_FILENO) == -1)
					return (print_error(main, errno));
			close(main->gap->pipe_in[1]);
		}
		if (main->gap->pipe_out != NULL)
		{
			if (main->gap->fd_out == 1)
				if (dup2(main->gap->pipe_out[1], STDOUT_FILENO) == -1)
					return (print_error(main, errno));
			close(main->gap->pipe_out[0]);
		}
	}
	if (dup2(main->gap->fd_out, STDOUT_FILENO) == -1)
		return (print_error(main, errno));
	if (dup2(main->gap->fd_in, STDIN_FILENO) == -1)
		return (print_error(main, errno));
}

static int	execute_builtins(t_main *main)
{
	if (mystrncmp(main->gap->comm, "env", 4) == 0)
		return (env(main));
	else if (mystrncmp(main->gap->comm, "pwd", 4) == 0)
		return (pwd(main));
	else if (mystrncmp(main->gap->comm, "echo", 5) == 0)
		return (echo(main));
	else if (ft_strncmp(main->gap->comm, "unset", 6) == 0)
		return (unset(main));
	else if (ft_strncmp(main->gap->comm, "export", 7) == 0)
		return (export(main));
	else if (ft_strncmp(main->gap->comm, "cd", 3) == 0)
		return (cd(main));
	else if (ft_strncmp(main->gap->comm, "exit", 5) == 0)
		return (ft_exit(main));
	else
		return (0);
}

static void	execute_bin(t_main *main)
{
	char	*file_path;
	char	**command;

	if (main->gap->syntax_flag == FALSE)
		return (exit(main->exit_status));
	if (main->gap->comm == NULL)
		return (exit(main->exit_status));
	command = parse_command(main->gap->arg, main->gap->comm);
	file_path = parse_filename(main->gap->comm, main->envp);
	execve(file_path, command, main->envp);
	print_error(main, errno);
	exit(main->exit_status);
}	

void	execute_pipe(t_main *main)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (print_error(main, errno));
	else if (pid != 0)
		signal(SIGINT, child_signal_handler);
	add_pid(main->pid, pid);
	if (pid == 0)
	{
		redir_pipe(main);
		if (execute_builtins(main))
			exit(0);
		execute_bin(main);
	}
}

void	execute(t_main *main)
{
	pid_t	pid;

	if (main->pipe == 1)
	{
		if (main->gap->syntax_flag == FALSE)
			return ;
		if (main->gap->comm == NULL)
			return ;
		if (execute_builtins(main))
			return ;
		pid = fork();
		if (pid == -1)
			return (print_error(main, errno));
		else if (pid != 0)
			signal(SIGINT, child_signal_handler);
		add_pid(main->pid, pid);
		if (pid == 0)
		{
			redir_pipe(main);
			execute_bin(main);
		}
		return ;
	}
	pipe_work(main);
}
