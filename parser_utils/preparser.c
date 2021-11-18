/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 18:01:29 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/18 14:46:42 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*chek_after_redirect(t_main *main, char *str)
{
	int		i;

	if (*str == *(str + 1))
		str++;
	str++;
	i = 0;
	while (1)
	{
		if (str[i] == '>' || str[i] == '<' || str[i] == '|' || str[i] == '\0'
			|| str[i] == '\n')
		{
			main->exit_status = E_SYNTAX;
			ft_error_in_shell(ERROR, NULL, "syntax error", 0);
			return (NULL);
		}
		if (str[i] != ' ' && str[i] != '	')
			return (str);
		i++;
	}
	return (str);
}

static char	*pre_quotes(t_main *main, char *str)
{
	char	c;

	c = *str;
	str++;
	while (*str != c)
	{
		if (*str == '\0')
		{
			main->exit_status = E_SYNTAX;
			ft_error_in_shell(ERROR, NULL, "syntax error", 0);
			return (NULL);
		}
		str++;
	}
	str++;
	return (str);
}

static int	check_pipe(t_main *main, char *str, int start, int finish)
{
	while (start <= finish)
	{
		if (str[start] == '|' || str[start] == '\0' || str[start] == '\n')
		{
			main->exit_status = E_SYNTAX;
			ft_error_in_shell(ERROR, NULL, "syntax error", 0);
			return (FALSE);
		}
		if (str[start] != ' ' && str[start] != '	')
			return (TRUE);
		start++;
	}
	main->exit_status = E_SYNTAX;
	ft_error_in_shell(ERROR, NULL, "syntax error", 0);
	return (FALSE);
}

int	pre_pipe(t_main *main, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			if (check_pipe(main, str, j, i) == FALSE)
				return (ERROR);
			i++;
			if (str[i] == '|')
				i++;
			if (check_pipe(main, str, i, ft_strlen(str)) == FALSE)
				return (ERROR);
			j = i;
		}
		i++;
	}
	return (NOT_ERROR);
}

int	preparser(t_main *main, char *str)
{
	main->pid = NULL;
	main->last_exit_status = main->exit_status;
	main->exit_status = 0;
	main->gap = initial_gap();
	if (main->gap == NULL)
	{
		main->exit_status = E_MALLOC;
		return (ERROR);
	}
	main->first_gap = main->gap;
	main->pipe = 1;
	if (pre_pipe(main, str) == ERROR)
		return (ERROR);
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
			str = pre_quotes(main, str);
		else if (str && (*str == '>' || *str == '<'))
			str = chek_after_redirect(main, str);
		else
			str++;
		if (main->exit_status != NOT_ERROR)
			return (ERROR);
	}
	return (NOT_ERROR);
}
