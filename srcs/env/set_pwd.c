/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skim2 <skim2@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 04:36:31 by skim2             #+#    #+#             */
/*   Updated: 2023/04/05 05:49:10 by skim2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_old_pwd(char ***envp)
{
	char	*old_pwd;
	char	*old_pwd_var;

	old_pwd = ft_strdup("OLDPWD");
	if (get_pwd(*envp))
		old_pwd_var = ft_strdup(&(get_pwd(*envp)[4]));
	else
		old_pwd_var = ft_strdup("");
	if (check_name(*envp, old_pwd))
		substitute_envp(*envp, old_pwd, old_pwd_var);
	else
		change_envp(envp, old_pwd, old_pwd_var);
}

char	*ft_getcwd(void)
{
	char	*buf;
	size_t	size;

	size = 1000;
	buf = (char *)malloc(sizeof(char) * size);
	if (!buf)
		exit(1);
	while (1)
	{
		buf = getcwd(buf, size);
		if (buf)
			return (buf);
		free(buf);
		size = 2 * 1000;
		buf = (char *)malloc(sizeof(char) * size);
		if (!buf)
			exit(1);
	}
}

void	set_pwd(char ***envp)
{
	char	*pwd;
	char	*line;

	pwd = ft_strdup("PWD");
	line = ft_getcwd();
	if (check_name(*envp, pwd))
		substitute_envp(*envp, pwd, line);
	else
		change_envp(envp, pwd, line);
}
