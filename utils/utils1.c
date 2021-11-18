/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ChelseyLeonia <ChelseyLeonia@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:06:42 by celys             #+#    #+#             */
/*   Updated: 2021/11/16 19:14:19 by ChelseyLeon      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* добавляет строку str в конец двумерного массива mas */
char	**ft_sstrjoin(char **mas, char *str)
{
	char	**new_mas;
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (mas[++i] != NULL)
		len++;
	new_mas = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new_mas)
		return (NULL);
	new_mas[len + 1] = NULL;
	new_mas[len] = NULL;
	i = -1;
	while (mas[++i] != NULL)
		new_mas[i] = mas[i];
	new_mas[i] = str;
	free(mas);
	return (new_mas);
}

int	ft_trim_empty(char *str, int *i)
{
	while (str[*i])
	{
		if (str[*i] != ' ' && str[*i] != '	')
			break ;
		(*i)++;
	}
	return (*i);
}

int	ft_check_redir_arg(char *arg)
{
	while (1)
	{
		if (*arg == '\0' || *arg == '\n')
			return (FALSE);
		if (*arg != '>' && *arg != '<' && *arg != '|')
			return (TRUE);
		arg++;
	}
	return (FALSE);
}

void	child_signal_handler(int signo)
{
	(void)signo;
}

char	*free_tmps(t_tmps tmps)
{
	if (tmps.tmp1)
		free (tmps.tmp1);
	if (tmps.tmp2)
		free (tmps.tmp2);
	if (tmps.tmp3)
		free (tmps.tmp3);
	if (tmps.tmp4)
		free (tmps.tmp4);
	return (NULL);
}
