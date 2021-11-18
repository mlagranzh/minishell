/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleonia <cleonia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:19:19 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/11 19:19:20 by cleonia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error_in_shell(int retval, char *arg, char *error, int error_key)
{
	ft_putstr_fd("minishell: ", 2);
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
		if (error)
			ft_putendl_fd(error, 2);
		else
			ft_putendl_fd(strerror(error_key), 2);
	}
	else if (error)
		ft_putendl_fd(error, 2);
	else
		ft_putendl_fd(strerror(error_key), 2);
	return (retval);
}

int	ft_free_str(int key, char *str)
{
	if (str)
		free(str);
	return (key);
}

int	ft_put_status_and_return(t_main *main, int key)
{
	main->exit_status = key;
	return (key);
}

int	ft_print_error_put_status(t_main *main, int key, char *error)
{
	main->exit_status = key;
	return (ft_error_in_shell(key, NULL, error, 0));
}
