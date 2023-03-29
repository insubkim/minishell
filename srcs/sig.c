#include "minishell.h"

struct termios *term;
void	sig_handler(int sig);

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void save_input_mode(struct termios *org_term)
{
        tcgetattr(STDIN_FILENO, org_term);
}
void set_input_mode(struct termios *new_term)
{
    tcgetattr(STDIN_FILENO, new_term);
    new_term->c_lflag &= ~(ICANON | ECHO);
    new_term->c_cc[VMIN] = 1;
    new_term->c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, new_term);
}
void reset_input_mode(struct termios *org_term)
{
    tcsetattr(STDIN_FILENO, TCSANOW, org_term);
}

void	set_signal()
{
	signal(SIGINT, sig_handler);
    signal(SIGQUIT, sig_handler);
}


void	ctrl_c(pid_t pid)
{
	if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	else
		ft_putstr_fd("\n", 1);}

void	sig_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		ctrl_c(pid);
	}
	if (sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", 1);
		}
		else
			ft_putstr_fd("\n", 1);
	}
}

int main(int argc, char **argv, char **envp)
{
    char    *line;
    //struct termios org_term;
    //struct termios new_term;
    
    term = (struct termios *)malloc(sizeof(struct termios) * 2);
    if (!term)
        return (0);
    // term[0] = org_term;
    // term[1] = new_term;
    set_signal();
    save_input_mode(&(term[0]));
    while ((line = readline("minishell> ")))
    {
        set_input_mode(&(term[1]));
        if (line)
        {
            if (ft_strlen(line) > 0)
            {
                add_history(line);
                if (!ft_is_space(line))
                    handle_line(line, envp);
            }
            free(line);
        }
        reset_input_mode(&(term[0]));
    }
    argc++;
    argv++;
    return (0);
}