/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:07:07 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/17 23:31:47 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_rewrite_strnstr(char *str_key, char *str_shell)
{
	int	i;
	int	k_len;
	int	s_len;

	i = 0;
	k_len = ft_strlen(str_key);
	s_len = ft_strlen(str_shell);
	while (i < k_len && i < s_len)
	{
		if (str_key[i] != str_shell[i])
			return (FALSE);
		i++;
	}
	if (str_key[i] == str_shell[i])
		return (TRUE);
	return (FALSE);
}

static void	put_in_fd(int fd, char *str_key)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str)
			break ;
		if (*str == '\0')
			rl_redisplay();
		if (ft_rewrite_strnstr(str_key, str) == TRUE)
		{
			free (str);
			break ;
		}
		write (fd, str, ft_strlen(str));
		write (fd, "\n", 1);
		free(str);
		rl_on_new_line();
	}
}

int	redirect_delimiter(t_main *main, char *str_key)
{
	int		fd;

	fd = open("delimiter", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		main->exit_status = E_FILE_OPEN;
		return (ft_error_in_shell(ERROR, "delimiter", NULL, errno));
	}
	put_in_fd(fd, str_key);
	close(fd);
	fd = open("delimiter", O_RDONLY, 0644);
	if (fd == -1)
	{
		main->exit_status = E_FILE_OPEN;
		return (ft_error_in_shell(ERROR, "delimiter", NULL, errno));
	}
	if (main->gap->fd_in != 0)
		close (main->gap->fd_in);
	main->gap->fd_in = fd;
	return (NOT_ERROR);
}
