/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:00:35 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/17 16:08:00 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_it_control_symbol(char c, int i, int j)
{
	if (((i == j) && (c == ' ' || c == '	'))
		|| c == '\'' || c == '\"' || c == '$')
		return (TRUE);
	return (FALSE);
}

static int	is_it_empty_end(char c)
{
	if (c == '\0' || c == ' ' || c == '	')
		return (TRUE);
	return (FALSE);
}

static int	parser_util1(t_main *main, char **str, int *i, int *j)
{
	int	flag;

	flag = FALSE;
	if (str[0][*i] == '\0' && (*i == *j))
	{
		(*i)++;
		return (flag);
	}
	if (is_it_control_symbol(str[0][*i], *i, *j) == TRUE)
		flag = control_symbol(main, str, i, j);
	else if (str[0][*i] == ' ' || str[0][*i] == '	' || str[0][*i] == '\0')
		comm_args(main, *str, i, j);
	else if ((str[0][*i] == '>' || str[0][*i] == '<'))
		redirect(main, str, i, j);
	else if (str[0][*i] == '|')
		pars_pipe(main, *str, i, j);
	else
		(*i)++;
	return (flag);
}

int	skipping_gap(char *str, int *i, int *j, t_main *main)
{
	if (main->gap->syntax_flag == FALSE)
		return (0);
	main->gap->syntax_flag = FALSE;
	while (str[*i] != '|' && str[*i] != '\0')
		(*i)++;
	if (str[*i] == '|')
		*j = *i;
	else
		return (1);
	return (0);
}

int	parser(char **str, t_main *main)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	if (preparser(main, *str) == ERROR)
		return (E_PREPARSER);
	while (1)
	{
		flag = parser_util1(main, str, &i, &j);
		if (main->exit_status != NOT_ERROR && skipping_gap(*str, &i, &j, main))
			return (ERROR);
		if (str[0][i - 1] == '\0')
			return (NOT_ERROR);
		if (flag == TRUE && is_it_empty_end(str[0][i]) == TRUE)
			comm_args(main, *str, &i, &j);
		if (main->exit_status != NOT_ERROR && skipping_gap(*str, &i, &j, main))
			return (ERROR);
		if (flag == TRUE && str[0][i] == '\0')
			return (NOT_ERROR);
	}
	return (ERROR);
}
