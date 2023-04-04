/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/04/05 06:13:15 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define NULL 0
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/wait.h>
# include  <sys/stat.h>
# include <sys/errno.h>

// forbidden functions
# include <string.h>
//-----------------------------------

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**file_redirection;
	char			*heredoc;
	int				pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_list
{
	t_cmd	*data;
}	t_list;

typedef struct s_separate_cmd
{
	int						startline;
	int						endline;
	char					*str;
	struct s_separate_cmd	*prev;
	struct s_separate_cmd	*next;
}	t_separate_cmd;

typedef struct s_parse
{
	int					redir_count;
	int					args_count;
	struct s_parse		*next;
}	t_parse;

typedef struct s_separate_list
{
	t_separate_cmd	*data;
}	t_separate_list;

//global variable
int				g_heredoc_sigint;

//handle
void			handle_line(char *line, char ***envp, \
				int *status, struct termios *term);

//readline
void			rl_replace_line(const char *text, int clear_undo);

//error
void			handle_redirection_error(int errnum, char *file_name);

//execute
void			execute_cmd_list(t_list *cmd_list, \
				char **envp, int *std_fd, int status);
void			redirection_input(char *file_name, int status, char **envp);
void			redirection_output(char *file_name, int status, char **envp);
void			redirection_output_append(char *file_name, \
				int status, char **envp);
void			redirection_heredoc(char *str);
char			*get_pathname(char *command, char **envp);
int				handle_heredoc(t_list *cmd_list, struct termios *term, \
				char **envp);
char			*get_file_name(char *file_arg, int status, char **envp);

//print
void			print_term(char *str);
void			print_term_exit(char *str, int exit_code);

//string
char			**ft_split(char const *s, char c);
void			ft_putstr_fd(char *s, int fd);
int				ft_strlen(char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_is_space(char *str);
char			*get_last_str(char **arr);
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_fd(char *s, int fd);
char			*ft_strdup(char *s);
int				is_char_space(char c);
char			*ft_substr(char *s, int start, int len);
int				is_printable(char c);
char			*heredoc_strjoin(char *s1, char *s2);
char			*ft_itoa(int n);
int				ft_atoi(const char *nptr);
char			*env_strjoin(char *s1, char *s2);

//quote
char			*delete_quote(char *s);
void			erase_quote(t_list *list);
int				check_list_quote(t_separate_list *list, int *status);

//signal
void			sig_handler(int sig);
void			set_signal(void);
void			ctrl_c(pid_t pid);
void			heredoc_set_signal(void);
void			heredoc_signal_handler(int sig);
int				check_quote(char *str);
void			is_quote(char *str, int *single_quote, int *double_quote);

//term
void			save_input_mode(struct termios *org_term);
void			set_input_mode(struct termios *new_term);
void			reset_input_mode(struct termios *org_term);

//struct create
void			add_first_separate(t_separate_list *separate_list);
void			create_cmd_list(t_separate_list *separate_list, char *line);
void			add_separate_cmd(t_separate_list *cmd_list);
void			add_cmd(t_list *cmd_list);
void			add_first_cmd(t_list *cmd_list);
void			add_parse(t_parse *parse, t_separate_list *list);

//init
t_separate_list	*init_cmd_list(void);
t_list			*init_list(void);
t_parse			*init_parse(void);
void			init_cmd(t_cmd *cmd);
void			init_separate(t_separate_cmd *cmd);
char			*delete_char(char *line);

//handle
void			ready_separate(t_separate_list *separate_list, \
				char *line, int *status);
void			reset_handle(int *std_fd, t_parse *parse, \
				t_list *list, t_separate_list *slist);
void			set_parse(t_list *list, t_separate_list *slist, \
				t_parse *parse);
void			set_cmd(t_list *list, int *str_fd);

//parsing
void			parsing(t_list *list, t_separate_list *sep_list, \
				t_parse *parse);
void			args_count(t_separate_list *list, t_parse *parse);
void			set_separate(t_separate_list *cmd_list, char *line);
int				sepatate_spaces(char *line, int i);
void			separate_line(t_separate_list *list, char *line, int *status);
int				count_word(char *line);
void			separate_dup(t_separate_list *list);
int				separate_spaces(char *line, int i);
int				separate_is_token(char *line, int i, int flag);
int				separate_is_token2(char *line, int i, int flag);
t_separate_cmd	*save_start_end(t_separate_cmd *cur, char *line, int i);

//env_parse
int				get_env_len(char *str);
char			*set_env_symbol(char *str, int *del, int status, char **envp);
void			check_env_symbol(t_cmd *cmd, int status);
char			*env_handle(char *line, int status, char **envp);

//builtin
int				is_builtin(t_cmd *cmd);
void			run_builtin(t_cmd *cmd, int *pipe, char **envp);
void			echo(t_cmd *cmd);
void			ft_export(t_cmd *cmd, int *pipe);
void			unset(t_cmd *cmd, int *pipe);
void			cd(t_cmd *cmd, int *pipe, char **envp);
int				is_valid_export_name(char c);
void			run_env(char **envp);
void			run_pwd(char **envp);
char			*get_pwd(char **envp);
void			cd(t_cmd *cmd, int *pipe, char **envp);
char	*get_old_pwd(char **envp);

//env
void			add_env(int fd, char ***envp);
void			delete_env(int fd, char ***envp);
void			change_dir(int fd, char ***envp, int *status);
int				get_status(int fd);
char			*get_line(int fd);
char	*set_line(char *line);
char	*get_name(char *line);
char	*get_var(char *line);
char	**reset_envp(char **envp, int i);
void	set_old_pwd(char ***envp);
char	*ft_getcwd(void);
int	check_name(char **envp, char *name);
void	substitute_envp(char **envp, char *name, char *var);
void	change_envp(char ***p_envp, char *name, char *var);
void	set_pwd(char ***envp);

//flag
int				flag_switch(int flag);

//free
void			free_parse(t_parse *parse);
void			free_cmd_list(t_list *cmd_list);
void			free_separate_list(t_separate_list *separate_list);
void			free_str_arr(char **str_arr);

#endif
