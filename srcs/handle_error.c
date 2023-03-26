/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: insub <insub@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 17:44:07 by insub             #+#    #+#             */
/*   Updated: 2023/03/26 17:54:31 by insub            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    handle_error(void)
{
    if (errno == ENOENT)
        print_term_exit("command not found", 127);
    else if (errno == EACCES)
        print_term_exit("permission denied", 1);
    else if (errno == EISDIR)
        print_term_exit("is a directory", 126);
    else if (errno == ENOEXEC)
        print_term_exit("cannot execute binary file", 126);
    else if (errno == E2BIG)
        print_term_exit("argument list too long", 126);
    else if (errno == ENAMETOOLONG)
        print_term_exit("file name too long", 126);
    else if (errno == ENFILE)
        print_term_exit("too many open files", 126);
    else if (errno == EMFILE)
        print_term_exit("too many open files", 126);
    else if (errno == ENOMEM)
        print_term_exit("not enough space", 126);
    else if (errno == ELOOP)
        print_term_exit("too many symbolic links encountered", 126);
    else if (errno == EFAULT)
        print_term_exit("bad address", 126);
    else if (errno == EIO)
        print_term_exit("i/o error", 126);
    else if (errno == EAGAIN)
        print_term_exit("resource temporarily unavailable", 126);
    else if (errno == EWOULDBLOCK)
        print_term_exit("resource temporarily unavailable", 126);
    else if (errno == EINTR)
        print_term_exit("interrupted function call", 126);
    else if (errno == EPIPE)
        print_term_exit("broken pipe", 126);
    else if (errno == EEXIST)
        print_term_exit("file exists", 126);
    else
        print_term_exit("error", 126);
}