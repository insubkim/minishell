/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/04/01 19:01:56 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define FT_WIFEXITED(status)       (((status) & 0x7f) == 0)
# define FT_WEXITSTATUS(status)     (((status) >> 8) & 0xff)
# define FT_WIFSTOPPED(status)      (((status) & 0xff) == 0x7f)
# define FT_WIFSIGNALED(status)     (((status) & 0x7f) && !WIFSTOPPED(status))
# define FT_WTERMSIG(status)        ((status) & 0x7f)
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
#include <sys/wait.h>
#include  <sys/stat.h>

// forbidden functions
# include <string.h>
//-----------------------------------

typedef struct s_cmd
{
    char    *cmd;
    char    **args;
    char    **file_redirection;
    char    *heredoc;
    int     pid;
    struct  s_cmd   *next;
}    t_cmd;

typedef struct s_list
{
    t_cmd           *data;
}   t_list;

typedef struct s_separate_cmd
{
    int     startline;
    int     endline;
    char    *str;
    struct s_separate_cmd   *prev;
    struct s_separate_cmd   *next;
}    t_separate_cmd;

typedef struct s_parse
{
    int     redir_count;
    int     args_count;
    struct s_parse *next;
}   t_parse;

typedef struct s_separate_list
{
    t_separate_cmd           *data;
}   t_separate_list;

//global variable
int     heredoc_sigint;

//handle
void	handle_line(char *line, char **envp, int *status, struct termios *term);

//readline
void    rl_replace_line (const char *text, int clear_undo);

//execute
void	execute_cmd_list(t_list *cmd_list, char **envp, int *std_fd);
void	redirection_input(char *file_name);
void	redirection_output(char *file_name);
void	redirection_output_append(char *file_name);
void	redirection_heredoc(char *str);
char	*get_pathname(char *command, char **envp);
int 	handle_heredoc(t_list *cmd_list, struct termios *term);
char	*heredoc_strjoin(char *s1, char *s2);

//print_term
void	print_term(char *str);
void	print_term_exit(char *str, int exit_code);

//string
char	**ft_split(char const *s, char c);
void    ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_is_space(char *str);
char    *get_last_str(char **arr);
int	    ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s);

//quote
char    *delete_quote(char *s);
void    erase_quote(t_list *list);

//signal
void    sig_handler(int sig);
void    set_signal();
void    ctrl_c(pid_t pid);

//term
void    save_input_mode(struct termios *org_term);
void    set_input_mode(struct termios *new_term);
void    reset_input_mode(struct termios *org_term);

//struct create
void    add_first_separate(t_separate_list *separate_list);
void    create_cmd_list(t_separate_list *separate_list, char *line);
void    add_separate_cmd(t_separate_list *cmd_list);
void    add_cmd(t_list *cmd_list);
void    add_first_cmd(t_list *cmd_list);
void    add_parse(t_parse *parse, t_separate_list *list);

//init
t_separate_list    *init_cmd_list();
t_list  *init_list();
t_parse *init_parse();
void    init_cmd(t_cmd *cmd);
void    init_separate(t_separate_cmd *cmd);

//parsing
void    parsing(t_list *list, t_separate_list *sep_list, t_parse *parse);
void    args_count(t_separate_list *list, t_parse *parse);
void    set_separate(t_separate_list *cmd_list, char *line);
int     sepatate_spaces(char *line, int i);
int     separate_line(t_separate_list *list, char *line, int *status);
int     count_word(char *line);
char	*get_file_name(char *file_arg);

//env_parse
int     is_char_space(char c);
int     get_env_len(char *str, int start);
char    *ft_substr(char *s, int start, int len);
char    *set_env_symbol(char *str, int start, int *del);
void    check_env_symbol(t_cmd *cmd);
void    env_handle(t_list  *list);

//flag
int     flag_switch(int flag);

#endif