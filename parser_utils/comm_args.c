/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comm_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:41:20 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/13 18:06:00 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	comm_args(t_main *main, char *str, int *i, int *j)
{
	char	**buffer;
	char	*sub_str;

	sub_str = ft_substr(str, *j, *i - *j);
	if (!sub_str)
		return (ft_put_status_and_return(main, E_MALLOC));
	if (!main->gap->comm)
		main->gap->comm = sub_str;
	else
	{
		buffer = ft_sstrjoin(main->gap->arg, sub_str);
		if (!buffer)
			return (ft_put_status_and_return(main, E_MALLOC));
		main->gap->arg = buffer;
	}
	ft_trim_empty(str, i);
	*j = *i;
	return (NOT_ERROR);
}
