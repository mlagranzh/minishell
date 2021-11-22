/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:41:32 by ChelseyLeon       #+#    #+#             */
/*   Updated: 2021/11/22 07:11:45 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_free_main(t_main *main, char *line)
{
	t_gap	*buf_gap;

	if (line)
		free (line);
	while (main->first_gap != NULL)
	{
		buf_gap = main->first_gap;
		if (main->first_gap->fd_in != 0)
			close(main->first_gap->fd_in);
		if (main->first_gap->fd_out != 1)
			close(main->first_gap->fd_out);
		if (main->first_gap->comm)
			free(main->first_gap->comm);
		if (main->first_gap->first_arg)
			free_2d_array(main->first_gap->first_arg);
		main->first_gap = main->first_gap->next;
		free(buf_gap);
	}
	if (main->pid)
		free(main->pid);
}

void	init_first_arg(t_main *main)
{
	t_gap	*buf_gap;

	buf_gap = main->gap;
	while (buf_gap != NULL)
	{
		buf_gap->first_arg = buf_gap->arg;
		buf_gap = buf_gap -> next;
	}
}

char	*ft_readline(void)
{
	char	*tmp1;
	char	*tmp2;
	char	**tmp3;
	char	*tmp4;
	char	*line;

	signal(SIGINT, signal_handler);
	tmp1 = getcwd(NULL, 0);
	tmp3 = ft_split(tmp1, '/');
	if (tmp3[0] != NULL)
		tmp4 = ft_strjoin(tmp3[len_2d_array(tmp3) - 1], " ");
	else
		tmp4 = ft_strdup("/");
	tmp2 = my_strjoin(READLINE_CYAN, "minishell \001➜\002 ", READLINE_YELLOW);
	free(tmp1);
	tmp1 = my_strjoin(tmp2, tmp4, READLINE_WHITE);
	line = readline(tmp1);
	free(tmp1);
	free_2d_array(tmp3);
	free(tmp4);
	free(tmp2);
	return (line);
}

int	print_main(t_main *main)
{
	int	i;

	printf("status=%i pipe_num=%i\n-------\n", main->exit_status, main->pipe);
	while (main->gap)
	{
		i = -1;
		printf("comm = {%s}\narg: ", main->gap->comm);
		if (main->gap->arg[0] == NULL)
			printf("{%s}", main->gap->arg[0]);
		while (main->gap->arg[++i] != NULL)
			printf("{%s}", main->gap->arg[i]);
		printf("\n");
		printf("fd_in: %i\n", main->gap->fd_in);
		printf("fd_out: %i\n", main->gap->fd_out);
		if (main->gap->syntax_flag == TRUE)
			printf("syntax_flag = TRUE\n");
		else
			printf("syntax_flag = FALSE\n");
		printf("-------\n");
		main->gap = main->gap->next;
	}
	return (0);
}
