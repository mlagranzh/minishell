/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: celys <celys@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:26:40 by celys             #+#    #+#             */
/*   Updated: 2021/11/17 22:02:24 by celys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include "LIBFT/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>

# define READLINE_BLACK		"\001\033[1;90m\002"
# define READLINE_RED		"\001\033[1;91m\002"
# define READLINE_GREEN		"\001\033[1;92m\002"
# define READLINE_YELLOW	"\001\033[1;93m\002"
# define READLINE_BLUE		"\001\033[1;94m\002"
# define READLINE_PURPLE	"\001\033[1;95m\002"
# define READLINE_CYAN		"\001\033[1;96m\002"
# define READLINE_WHITE		"\001\033[1;97m\002"
# define READLINE_RESET		"\001\033[0m\002"

typedef struct s_gap
{
	char			*comm;
	char			**arg;
	int				fd_in;
	int				fd_out;
	int				*pipe_in;
	int				*pipe_out;
	int				redir_flag;
	int				if_arg;
	char			**first_arg;
	int				syntax_flag;
	struct s_gap	*next;
}	t_gap;

typedef struct s_main
{
	int		pipe;
	pid_t	*pid;
	char	**envp;
	int		exit_status;
	int		last_exit_status;
	t_gap	*gap;
	t_gap	*first_gap;
}	t_main;

typedef struct s_tmps
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	char	*tmp4;
	char	**tmp5;
	char	**tmp6;
}	t_tmps;

/* parser function */
int		parser(char **str, t_main *main);
int		preparser(t_main *main, char *str);
char	*quotes1(char *str, int *i);
char	*quotes2(char *str, int *i, char **envp, int status);
int		args(t_gap *gap, char *str, int i, int last_pos);
void	pars_pipe(t_main *main, char *str, int *i, int *j);
int		comm_args(t_main *main, char *str, int *i, int *j);
int		control_symbol(t_main *main, char **str, int *i, int *j);
/* dollar */
char	*dollar(char *str, int *i, char **envp, int status);
char	*it_is_digit(char *str, int *i, int j);
char	*envp_search(char *tmp2, char **envp, int keylen);
int		ft_iskey(char c);
/* redirect */
void	redirect(t_main *main, char **str, int *i, int *j);
int		*ft_numjoin(int *mas, int num);
int		ft_redirect_in(t_main *main, char *file_name);
int		ft_redirect_out_append(t_main *main, char *file_name);
int		ft_redirect_out(t_main *main, char *file_name);
int		redirect_delimiter(t_main *main, char *str_key);

/* our_builtins */
int		export(t_main *main);
int		unset(t_main *main);
int		pwd(t_main *main);
int		echo(t_main *main);
int		env(t_main *main);
int		cd(t_main *main);
int		ft_exit(t_main *main);

/* execute */
void	execute(t_main *main);
char	*ft_getenv(char **envp, char *key);
void	exit_exec(t_main *main, int exit_status);
int		invalid_key(char *key, t_main *main);

/* utils0 */
char	**utils_parse_filename(char **envp);
char	*parse_filename(char *command, char **envp);
char	**parse_command(char **arguments, char *command);
void	my_putstr_fd(char *s1, char *s2, char *s3, int fd);
int		mystrncmp(char *s1, char *s2, size_t n);
/* utils1 */
char	**ft_sstrjoin(char **mas, char *str);
int		ft_trim_empty(char *str, int *i);
void	child_signal_handler(int signo);
int		ft_check_redir_arg(char *arg);
char	*free_tmps(t_tmps tmps);
/* utils2 */
size_t	len_2d_array(char **string);
char	**array_2d_dup(char **array);
t_gap	*initial_gap(void);
char	**sort_dictionary(char **dictionary);
/* utils3 */
void	exit_exec(t_main *main, int exit_status);
int		key_dict(char **dictionary, char *key);
char	*ft_getenv(char **envp, char *key);
void	print_error(t_main *main, int err_num);
t_tmps	*init_tmps(void);
/* utils4 */
char	*my_strjoin(char *s1, char *s2, char *s3);
int		i_strchr(const char *s, int c);
void	add_pid(int *pid, int pid_value);
void	init_pid(t_main *main);
void	wait_pid(t_main *main);
/* utils5 */
char	*malloc_ch(size_t size);
char	**malloc_ch_ch(size_t size);
int		**malloc_int_int(size_t size);
int		*malloc_int(size_t size);
/* utils6 */
int		**free_2d_int(int **array);
void	my_free(char *string);
int		free_ret(t_tmps *tmps, int ret);
char	**ft_realloc(char **old, size_t size);
char	**free_2d_array(char **p);
/* utils7 */
char	*ft_readline(char **envp);
void	init_first_arg(t_main *main);
void	ft_free_main(t_main *main, char *line);
void	signal_handler(int signo);
int		print_main(t_main *main);

/* pipe */
void	pipe_work(t_main *main);
void	execute_pipe(t_main *main);

//error
int		ft_error_in_shell(int retval, char *arg, char *error, int error_key);
int		ft_print_error_put_status(t_main *main, int key, char *error);
void	ft_error(int key);
int		ft_free_str(int key, char *str);
int		ft_put_status_and_return(t_main *main, int key);

enum e_redirect
{
	R_IN = 1,
	R_OUT = 2,
	R_IN_DELIMITER = 3,
	R_OUT_APPEND = 4,
	R_FALSE = 0
};

enum e_bool
{
	TRUE = -10,
	FALSE = -20
};

enum e_errors
{
	NOT_ERROR = 0,
	ERROR = -1,
	E_MALLOC = 3,
	E_FILE_OPEN = 1,
	E_SYNTAX = 258,
	E_COMNOT = 127,
	E_PREPARSER = 259
};

#endif