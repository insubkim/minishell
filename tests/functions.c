/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inskim <inskim@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 23:42:25 by inskim            #+#    #+#             */
/*   Updated: 2023/03/18 03:23:27 by inskim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <readline/readline.h>
// #include <readline/history.h>
// #include <stdlib.h>

// int main(int argc, char *argv[])
// {
//     char *s =readline(">");
    
//     printf("[ %s ]\n",s);
//     add_history(s);
//     rl_clear_history();

//     free(s);
//      rl_on_new_line();
//      rl_redisplay();
//     s =readline(">");

   
//     //rl_redisplay();
//     printf("[ %s ]\n",s);
//     free(s);
//     s = 0;
//    // system("leaks a.out");
//     return (0);
// }


#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    // Read a line of input using readline
    char* input = readline("Enter some text: ");

  //  rl_redisplay();
    rl_replace_line("hello", 1);
    rl_redisplay();
    // Add the input to the history list
    input = readline("Enter some text: ");

    add_history(input);

    // Clear the history list
    rl_clear_history();

    // Free the input string returned by readline
    free(input);

    return 0;
}