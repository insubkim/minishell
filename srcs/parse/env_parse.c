/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 15:51:46 by skim2             #+#    #+#             */
/*   Updated: 2023/04/05 03:18:40 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_len(char *str)
{
	int	end;
	int	len;

	end = 0;
	len = 0;
	while (str[end])
	{
		if (str[end] == '\'' || str[end] == '\"' || str[end] == '<' \
				|| str[end] == '>' || str[end] == '|' || str[end] == ' '
			|| str[end] == '$' || is_char_space(str[end]))
			break ;
		end++;
		len++;
	}
	return (len);
}

char	*ft_get_env(char *env, int status, char **envp)
{
	int		i;
	int		len;
	char	*tmp;

	len = 0;
	i = 0;
	if (!ft_strcmp(env, "?"))
		return (ft_itoa(status));
	while (envp[i])
	{
		if (!strncmp(env, envp[i], ft_strlen(env))
			&& envp[i][ft_strlen(env)] == '=')
			break ;
		i++;
	}
	if (!envp[i])
		return (0);
	tmp = ft_strdup(envp[i] + ft_strlen(env) + 1);
	return (tmp);
}

char	*set_env_symbol(char *str, int *del, int status, char **envp)
{
	int		env_len;
	char	*env;
	char	*tmp;

	env_len = get_env_len(str);
	env = ft_substr(str, 0, env_len);
	tmp = ft_get_env(env, status, envp);
	if (!tmp)
		*del = 1;
	free(env);
	tmp = heredoc_strjoin(tmp, &str[env_len]);
	return (tmp);
}

int	check_redir_env(char *line, int i)
{
	i--;
	while (i > 0 && line[i] == ' ')
		i--;
	while (i > 0)
	{
		if (line[i] == '<' && line[i - 1] == '<')
			return (0);
		i--;
	}
	return (1);
}

char	*env_handle(char *l, int status, char **envp)
{
	int	i;
	int	s_flag;
	int	d_flag;
	int	del;

	del = 0;
	s_flag = 0;
	d_flag = 0;
	i = 0;
	while (l[i] != '\0')
	{
		del = 0;
		if ((d_flag || !s_flag) && l[i] == '$' && check_redir_env(l, i))
		{
			l[i] = 0;
			l = env_strjoin(l, set_env_symbol(&l[i + 1], &del, status, envp));
		}
		if (!d_flag && l[i] == '\'' && !del)
			s_flag = flag_switch(s_flag);
		if (!s_flag && l[i] == '\"' && !del)
			d_flag = flag_switch(d_flag);
		if (!del)
			i++;
	}
	return (l);
}
