/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 19:14:24 by cleonia           #+#    #+#             */
/*   Updated: 2021/11/18 19:18:00 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	redir_open_file(t_main *main, char *redir_arg, int empty_flag)
{
	int	retval;

	if (ft_check_redir_arg(redir_arg) == FALSE && empty_flag != 0)
	{
		main->exit_status = E_SYNTAX;
		return (ft_error_in_shell(ERROR, NULL, "syntax error", 0));
	}
	if (main->gap->redir_flag == R_OUT)
		retval = ft_redirect_out(main, redir_arg);
	if (main->gap->redir_flag == R_OUT_APPEND)
		retval = ft_redirect_out_append(main, redir_arg);
	if (main->gap->redir_flag == R_IN)
		retval = ft_redirect_in(main, redir_arg);
	if (main->gap->redir_flag == R_IN_DELIMITER)
		retval = redirect_delimiter(main, redir_arg);
	main->gap->redir_flag = R_FALSE;
	return (retval);
}

static int	is_it_redirect(int *redir_flag, char *str, int *i)
{
	if (str[*i] == '>')
	{
		(*i)++;
		*redir_flag = R_OUT;
		if (str[*i] == '>')
		{
			(*i)++;
			*redir_flag = R_OUT_APPEND;
		}
	}
	else if (str[*i] == '<')
	{
		(*i)++;
		*redir_flag = R_IN;
		if (str[*i] == '<')
		{
			(*i)++;
			*redir_flag = R_IN_DELIMITER;
		}
	}
	else
		return (FALSE);
	return (TRUE);
}

static char	*redir_control_symbol(t_main *main, char *str, int *i)
{
	while (str[*i] != ' ' && str[*i] != '	' && str[*i] != '\0'
		&& str[*i] != '>' && str[*i] != '<' && str[*i] != '|')
	{
		if (str[*i] == '\'')
			str = quotes1(str, i);
		else if (str && str[*i] == '\"')
			str = quotes2(str, i, main -> envp, main->exit_status);
		else if (str && str[*i] == '$')
			str = dollar(str, i, main -> envp, main->exit_status);
		else
			(*i)++;
	}
	if (!str)
		main->exit_status = E_MALLOC;
	return (str);
}

void	redirect(t_main *main, char **str, int *i, int *j)
{
	char	*buf_str;
	int		retval;

	if (*i != *j && comm_args(main, *str, i, j) != NOT_ERROR)
		return ;
	is_it_redirect(&main->gap->redir_flag, *str, i);
	ft_trim_empty(*str, i);
	*j = *i;
	*str = redir_control_symbol(main, *str, i);
	if (!(*str))
		return ;
	buf_str = ft_substr(*str, *j, *i - *j);
	if (!buf_str)
	{
		main->exit_status = E_MALLOC;
		return ;
	}
	retval = redir_open_file(main, buf_str, *i - *j);
	free (buf_str);
	if (retval != NOT_ERROR)
		return ;
	*j = *i;
}
