/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:43:44 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/17 20:28:58 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_pipe(t_main *main, char *str, int *i, int *j)
{
	if (*i == *j && !main->gap->comm && main->gap->fd_in == 0
		&& main->gap->fd_out == 1)
	{
		ft_print_error_put_status(main, E_SYNTAX, "syntax error");
		return ;
	}
	if (*i != *j && comm_args(main, str, i, j) != NOT_ERROR)
		return ;
	(*i)++;
	if (str[*i] == '|')
		(*i)++;
	*j = *i;
	main->pipe++;
	main->gap->next = initial_gap();
	if (!main->gap->next)
	{
		main->exit_status = E_MALLOC;
		return ;
	}
	main->exit_status = 0;
	main->gap = main->gap->next;
}
