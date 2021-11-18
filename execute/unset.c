/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 16:11:30 by banji             #+#    #+#             */
/*   Updated: 2021/11/16 18:28:53 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_utils(t_main *main)
{
	char	**new_envp;
	char	**tmp1;
	int		i;
	int		j;

	i = -1;
	j = -1;
	new_envp = malloc_ch_ch(sizeof(char *) * (len_2d_array(main->envp) + 1));
	while (main->envp[++j] != NULL)
	{
		tmp1 = ft_split(main->envp[j], '=');
		if (ft_strncmp(tmp1[0], *main->gap->arg, ft_strlen(tmp1[0]) + 1) == 0)
			j++;
		tmp1 = free_2d_array(tmp1);
		if (main->envp[j])
			new_envp[++i] = ft_strdup(main->envp[j]);
		else
			break ;
	}
	new_envp[i + 1] = NULL;
	main->envp = free_2d_array(main->envp);
	main->envp = new_envp;
}

int	unset(t_main *main)
{
	char	*search_key;

	while (*main->gap->arg != NULL)
	{
		if (invalid_key(*main->gap->arg, main))
			continue ;
		search_key = ft_getenv(main->envp, *main->gap->arg);
		if (search_key == NULL)
		{
			free(search_key);
			main->gap->arg++;
			continue ;
		}
		free(search_key);
		unset_utils(main);
		main->gap->arg++;
	}
	exit_exec(main, 0);
	return (1);
}
