/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:53:12 by inskim            #+#    #+#             */
/*   Updated: 2023/03/31 17:31:43 by inskim           ###   ########.fr       */
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
}    t_cmd;

typedef struct s_list
{
    t_cmd           *data;
    struct s_list   *next;
}   t_list;

struct termios term[2];

void	handle_line(char *line, char **envp, int *status);
void    rl_replace_line (const char *text, int clear_undo);
void	execute_cmd_list(t_list *cmd_list, char **envp, int *std_fd);
void	redirection_input(char *file_name);
void	redirection_output(char *file_name);
void	redirection_output_append(char *file_name);
void	redirection_heredoc(char *str);
char	*get_pathname(char *command, char **envp);
void	print_term(char *str);
void	print_term_exit(char *str, int exit_code);
void	handle_heredoc(t_list *cmd_list);

//문자열 관련
char	**ft_split(char const *s, char c);
void    ft_putstr_fd(char *s, int fd);
int     ft_strlen(char *s);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_is_space(char *str);
char    *get_last_str(char **arr);
int	ft_strcmp(char *s1, char *s2);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strdup(char *s);
//시그널 설정
void    sig_handler(int sig);
void    set_signal();
void    ctrl_c(pid_t pid);
//터미널 설정
void save_input_mode(struct termios *org_term);
void set_input_mode(struct termios *new_term);
void reset_input_mode(struct termios *org_term);

#endif