/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:08:30 by celys             #+#    #+#             */
/*   Updated: 2021/11/17 04:36:54 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exit_exec(t_main *main, int exit_status)
{
	if (main->pipe > 1)
		exit(exit_status);
	else
		main->exit_status = exit_status;
}

int	key_dict(char **dictionary, char *key)
{
	char	**key_value;
	int		i;

	i = 0;
	while (dictionary[i] != NULL)
	{
		key_value = ft_split(dictionary[i], '=');
		if (!ft_strncmp(key, key_value[0], ft_strlen(key) + 1))
		{
			key_value = free_2d_array(key_value);
			return (i);
		}
		key_value = free_2d_array(key_value);
		i++;
	}
	return (-1);
}

char	*ft_getenv(char **envp, char *key)
{
	char	**current;
	char	*output;
	int		i;

	if (key == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		current = ft_split(envp[i], '=');
		if (ft_strncmp(key, current[0], ft_strlen(key) + 1) == 0)
		{
			output = ft_strdup(current[1]);
			current = free_2d_array(current);
			return (output);
		}
		i++;
		current = free_2d_array(current);
	}
	return (NULL);
}

void	print_error(t_main *main, int err_num)
{
	main->exit_status = 1;
	if (err_num == 2)
	{
		my_putstr_fd("minishell: ", main->gap->comm, \
						": No such file or directory\n", 2);
		main->exit_status = 127;
	}
	else if (err_num == 13)
	{
		my_putstr_fd("minishell: ", main->gap->comm, ": Permission denied\n", 2);
		main->exit_status = 126;
	}
	else if (err_num == 14)
	{
		my_putstr_fd("minishell: ", main->gap->comm, ": command not found\n", 2);
		main->exit_status = 127;
	}
	else if (err_num == 0)
	{
		my_putstr_fd("minishell: ", main->gap->comm, ": '", 2);
		my_putstr_fd(*main->gap->arg, "': not a valid identifier\n", NULL, 2);
	}
	else
		perror(main->gap->comm);
}

t_tmps	*init_tmps(void)
{
	t_tmps	*tmps;

	tmps = malloc(sizeof(*tmps));
	tmps->tmp1 = NULL;
	tmps->tmp2 = NULL;
	tmps->tmp3 = NULL;
	tmps->tmp4 = NULL;
	tmps->tmp5 = NULL;
	return (tmps);
}
