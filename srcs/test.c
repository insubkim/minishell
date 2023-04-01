
#include "../minishell.h"

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

char	*heredoc_strjoin(char *s1, char *s2)
{
	int		len;
	char	*p;
	int		i;

	if (!s1)
		len = ft_strlen(s2);
	else 
		len = ft_strlen(s1) + ft_strlen(s2);
	p = (char *)malloc(sizeof(char) * (len + 1));
	if (!p)
		exit(127);
	i = 0;
	while (s1 && s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (*s2)
		p[i++] = *s2++;
	p[i] = 0;
	free(s1);
	return (p);
}

int flag_switch(int flag)
{
    return (!flag);
}

char    *delete_quote(char *s)
{
    int single_flag;
    int double_flag;
    int i;

    single_flag = 0;
    double_flag = 0;
    i = -1;
    while (s[++i])
    {
        if (!double_flag && s[i] == '\'')
        {
            single_flag = flag_switch(single_flag);
            s[i] = 0;
            s = heredoc_strjoin(s, &(s[i-- + 1]));
        }
        if (!single_flag && s[i] == '\"')
        {
            double_flag = flag_switch(single_flag);
            s[i] = 0;
            s = heredoc_strjoin(s, &(s[i-- + 1]));
        }
    }
    return (s);
}

int main()
{
    char *s = strdup(" .    \' .  a\'");
    printf("%s\n", delete_quote(s));
}