/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:06:15 by celys             #+#    #+#             */
/*   Updated: 2021/11/17 20:32:56 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**utils_parse_filename(char **envp)
{
	char	**parse_1;
	char	**parse_2;
	int		i;

	i = 0;
	while ((ft_strncmp(envp[i], "PATH=", 5) != 0))
	{
		i++;
		if (envp[i] == NULL)
			return (NULL);
	}
	parse_1 = ft_split(envp[i], '=');
	parse_2 = ft_split(parse_1[1], ':');
	parse_1 = free_2d_array(parse_1);
	return (parse_2);
}

char	*parse_filename(char *command, char **envp)
{
	int		i;
	char	**parse_1;
	char	*parse_2;

	if (command[0] == '/' || (command[0] == '.' && command[1] == '/'))
		return (command);
	parse_1 = utils_parse_filename(envp);
	if (parse_1 == NULL)
		return (NULL);
	i = -1;
	while (1)
	{
		parse_2 = my_strjoin(parse_1[++i], "/", command);
		if (access(parse_2, X_OK) != -1)
		{
			parse_1 = free_2d_array(parse_1);
			return (parse_2);
		}
		free(parse_2);
		if (parse_1[i] == NULL)
		{
			parse_1 = free_2d_array(parse_1);
			return (NULL);
		}
	}
}

char	**parse_command(char **arguments, char *command)
{
	char	**parse_command;
	int		i;

	i = 1;
	parse_command = malloc_ch_ch(sizeof(char *) * \
									(2 + len_2d_array(arguments)));
	parse_command[0] = command;
	if (arguments)
	{
		while (arguments[i - 1] != NULL)
		{
			parse_command[i] = arguments[i - 1];
			i++;
		}
	}
	parse_command[i] = NULL;
	return (parse_command);
}

void	my_putstr_fd(char *s1, char *s2, char *s3, int fd)
{
	char	*tmp;

	tmp = my_strjoin(s1, s2, s3);
	ft_putstr_fd(tmp, fd);
	free(tmp);
}

int	mystrncmp(char *s1, char *s2, size_t n)
{
	size_t	iter;
	char	*p1;
	char	*p2;

	iter = 0;
	p1 = s1;
	p2 = s2;
	while (ft_tolower(*p1) == ft_tolower(*p2) && iter < n)
	{
		if (*p1 == '\0' || *p2 == '\0')
			return (0);
		iter++;
		p1++;
		p2++;
	}
	if (iter != n)
		return (*(unsigned char *)p1 - *(unsigned char *)p2);
	return (0);
}
