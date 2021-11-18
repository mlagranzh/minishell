/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:21:53 by celys             #+#    #+#             */
/*   Updated: 2021/11/17 02:02:16 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static __int128_t	ft_atoll(char *str)
{
	size_t			i;
	__int128_t		output;
	int				minus;

	i = 0;
	output = 0;
	minus = 1;
	if (ft_strncmp(str, "-9223372036854775808", 21) == 0)
		return (LONG_LONG_MIN);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			minus = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		output = output * 10 + str[i] - '0';
		i++;
	}
	return (output * minus);
}

static int	my_isdigit(char *string)
{
	int	i;

	i = 0;
	if (string[i] == '-' || string[i] == '+')
	{
		if (string[i] == '-')
			i++;
	}
	if (string[i] == '\0')
		return (0);
	while (string[i] != '\0')
	{
		if (!(string[i] >= '0' && string[i] <= '9'))
			return (0);
		i++;
	}
	if (ft_strlen(string) >= 19)
	{
		if (ft_strncmp(string, "-9223372036854775808", 21) == 0)
			return (1);
		if (ft_strncmp(string, "9223372036854775807", 20) == 0)
			return (1);
		return (0);
	}
	return (1);
}

int	ft_exit(t_main *main)
{
	int	i;

	if (main->pipe == 1)
		ft_putstr_fd("exit\n", 2);
	if (*main->gap->arg == NULL)
		exit(main->exit_status);
	i = -1;
	while (main->gap->arg[++i] != NULL)
	{
		if (!my_isdigit(main->gap->arg[i]) && !my_isdigit(main->gap->arg[0]))
		{
			my_putstr_fd("minishell: exit: ", *main->gap->arg, \
							": numeric argument required\n", 2);
			exit(255);
		}
	}
	if (i > 1)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		exit_exec(main, 1);
		return (1);
	}
	main->exit_status = (int) ft_atoll(main->gap->arg[--i]);
	exit(main->exit_status);
	return (1);
}
