/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:05:11 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 19:05:51 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	*ft_numjoin(int *mas, int num)
{
	int	*new_mas;
	int	mas_len;
	int	i;

	mas_len = 0;
	while (mas[mas_len] > 1)
		mas_len++;
	new_mas = (int *)malloc(sizeof(int) * (mas_len + 2));
	if (!new_mas)
		return (NULL);
	i = 0;
	while (mas[i] > 1)
	{
		new_mas[i] = mas[i];
		i++;
	}
	new_mas[i] = num;
	new_mas[i + 1] = -1;
	free (mas);
	return (new_mas);
}

int	ft_redirect_out(t_main *main, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		main->exit_status = E_FILE_OPEN;
		return (ft_error_in_shell(ERROR, file_name, NULL, errno));
	}
	if (main->gap->fd_out != 1)
		close (main->gap->fd_out);
	main->gap->fd_out = fd;
	return (NOT_ERROR);
}

int	ft_redirect_out_append(t_main *main, char *file_name)
{
	int	fd;

	fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		main->exit_status = E_FILE_OPEN;
		return (ft_error_in_shell(ERROR, file_name, NULL, errno));
	}
	if (main->gap->fd_out != 1)
		close (main->gap->fd_out);
	main->gap->fd_out = fd;
	return (NOT_ERROR);
}

int	ft_redirect_in(t_main *main, char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY, 0644);
	if (fd == -1)
	{
		main->exit_status = E_FILE_OPEN;
		return (ft_error_in_shell(ERROR, file_name, NULL, errno));
	}
	if (main->gap->fd_in != 0)
		close (main->gap->fd_in);
	main->gap->fd_in = fd;
	return (NOT_ERROR);
}
