/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 21:48:38 by celys             #+#    #+#             */
/*   Updated: 2021/11/19 02:16:27 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	invalid_key(char *key, t_main *main)
{
	int	i;

	if (*key == '\0')
	{
		print_error(main, 0);
		main->gap->arg++;
		if (main->gap->arg != NULL)
			exit_exec(main, 1);
		return (1);
	}
	i = -1;
	while (key[++i] != '\0')
	{
		if ((key[0] >= '0' && key[0] <= '9') || \
		(!((key[i] >= '0' && key[i] <= '9') || (key[i] >= 'A' && key[i] <= 'Z') \
		|| (key[i] >= 'a' && key[i] <= 'z') || key[i] == '_')))
		{
			print_error(main, 0);
			main->gap->arg++;
			if (main->gap->arg != NULL)
				exit_exec(main, 1);
			return (1);
		}
	}
	return (0);
}

static	int	print_export(char **envp, int fd_out)
{
	char	**new_dict;
	size_t	i;
	char	**tmp;

	i = 0;
	new_dict = sort_dictionary(envp);
	while (i < len_2d_array(envp))
	{
		ft_putstr_fd("declare -x ", fd_out);
		tmp = ft_split(new_dict[i], '=');
		ft_putstr_fd(tmp[0], fd_out);
		if (tmp[1])
		{
			ft_putstr_fd("=\"", fd_out);
			ft_putstr_fd(tmp[1], fd_out);
			ft_putstr_fd("\"", fd_out);
		}
		ft_putstr_fd("\n", fd_out);
		free_2d_array(tmp);
		i++;
	}
	new_dict = free_2d_array(new_dict);
	return (1);
}

static void	join_value(t_main *main, char **key, char **value, t_tmps	*tmps)
{
	if (ft_strlen((*key)) > 1)
	{
		if ((*key)[ft_strlen((*key)) - 1] == '+')
		{
			tmps->tmp2 = (*key);
			(*key) = ft_substr((*key), 0, ft_strlen((*key)) - 1);
			if (key_dict(main->envp, (*key)) != -1)
			{
				tmps->tmp5 = ft_split \
					(main->envp[key_dict(main->envp, (*key))], '=');
				tmps->tmp4 = (*value);
				(*value) = ft_strjoin(tmps->tmp5[1], (*value));
			}
		}
	}
}

static int	export_utils(t_main *main, char **key, char **value)
{
	t_tmps	*tmps;
	int		idx;

	tmps = init_tmps();
	join_value(main, key, value, tmps);
	if (invalid_key((*key), main))
		return (free_ret(tmps, 1));
	tmps->tmp1 = ft_getenv(main->envp, (*key));
	if (tmps->tmp1)
	{
		idx = key_dict(main->envp, (*key));
		tmps->tmp3 = main->envp[idx];
		main->envp[idx] = my_strjoin((*key), "=", (*value));
		if (main->gap->arg + 1 == NULL)
			exit_exec(main, 0);
		main->gap->arg++;
		return (free_ret(tmps, 1));
	}
	return (free_ret(tmps, 0));
}

int	export(t_main *main)
{
	t_tmps	*tmps;

	if (*main->gap->arg == NULL)
		return (print_export(main->envp, main->gap->fd_out));
	tmps = init_tmps();
	while (*main->gap->arg != NULL)
	{
		my_free(tmps->tmp1);
		my_free(tmps->tmp2);
		tmps->tmp1 = ft_substr(*main->gap->arg, 0, \
									i_strchr(*main->gap->arg, '='));
		tmps->tmp2 = ft_substr(*main->gap->arg, \
				i_strchr(*main->gap->arg, '=') + 1, ft_strlen(*main->gap->arg));
		if (export_utils(main, &tmps->tmp1, &tmps->tmp2))
			continue ;
		main->envp = ft_realloc(main->envp, sizeof(*main->envp) * \
									(len_2d_array(main->envp) + 2));
		main->envp[len_2d_array(main->envp)] = my_strjoin \
												(tmps->tmp1, "=", tmps->tmp2);
		main->gap->arg++;
		if (main->gap->arg + 1 == NULL)
			exit_exec(main, 0);
	}
	return (free_ret(tmps, 1));
}
