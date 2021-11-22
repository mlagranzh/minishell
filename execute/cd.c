/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:11:30 by banji             #+#    #+#             */
/*   Updated: 2021/11/22 07:11:23 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_error(char *error, t_main *main)
{
	ft_putendl_fd(error, 2);
	exit_exec(main, 1);
	return (0);
}

static int	cd_home(t_main *main)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_getenv(main->envp, "HOME");
	if (!tmp1)
	{
		free(tmp1);
		return (1);
	}
	tmp2 = ft_strdup(main->gap->arg[0]);
	main->gap->first_arg = free_2d_array(main->gap->first_arg);
	main->gap->arg = malloc_ch_ch(sizeof(*main->gap->arg) * 2);
	if (ft_strchr(tmp2, '~') == NULL)
		main->gap->arg[0] = ft_strdup(tmp1);
	else
		main->gap->arg[0] = ft_strjoin(tmp1, tmp2 + 1);
	main->gap->arg[1] = NULL;
	main->gap->first_arg = main->gap->arg;
	free(tmp1);
	free(tmp2);
	return (0);
}

static int	cd_utils(t_main *main)
{
	if (main->gap->arg[0] == NULL)
	{
		if (cd_home(main))
			return (cd_error("minishell: cd: HOME not set", main));
	}
	else if (main->gap->arg[0][0] == '-')
	{
		main->gap->first_arg = free_2d_array(main->gap->first_arg);
		main->gap->arg = malloc_ch_ch(sizeof(*main->gap->arg) * 2);
		main->gap->arg[0] = ft_getenv(main->envp, "OLDPWD");
		main->gap->arg[1] = NULL;
		main->gap->first_arg = main->gap->arg;
		if (main->gap->arg[0])
			ft_putendl_fd(main->gap->arg[0], 1);
		else
			return (cd_error("minishell: cd: OLDPWD not set", main));
	}
	else if (main->gap->arg[0][0] == '~')
	{
		if (cd_home(main))
			return (cd_error("minishell: cd: HOME not set", main));
	}
	return (1);
}

static void	cd_export(t_main *main, t_tmps	*tmps)
{
	main->gap->first_arg = free_2d_array(main->gap->first_arg);
	main->gap->arg = malloc_ch_ch(sizeof(char *) * 3);
	main->gap->arg[0] = ft_strjoin("OLDPWD=", tmps->tmp2);
	main->gap->arg[1] = ft_strjoin("PWD=", tmps->tmp1);
	main->gap->arg[2] = NULL;
	main->gap->first_arg = main->gap->arg;
	export(main);
}

int	cd(t_main *main)
{
	t_tmps	*tmps;

	tmps = init_tmps();
	if (!cd_utils(main))
		return (free_ret(tmps, 1));
	tmps->tmp2 = getcwd(NULL, 0);
	if (chdir(main->gap->arg[0]) == -1)
	{
		my_putstr_fd("minishell: cd: ", main->gap->arg[0], \
						": No such file or directory\n", 2);
		exit_exec(main, 1);
		return (free_ret(tmps, 1));
	}
	tmps->tmp1 = getcwd(NULL, 0);
	if (tmps->tmp1 == NULL)
	{
		print_error(main, errno);
		return (free_ret(tmps, 1));
	}
	cd_export(main, tmps);
	exit_exec(main, 0);
	return (free_ret(tmps, 1));
}
