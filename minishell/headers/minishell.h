/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:50:03 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:50:04 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// open()
// O_APPEND
// O_CREAT
// O_EXCL
// O_RDONLY
// O_TRUNC
// O_WRONLY
# include <fcntl.h>

// add_history()
# include <readline/history.h>

// readline()
// rl_clear_history() 
// rl_on_new_line()
// rl_redisplay()
// rl_replace_line()
# include <readline/readline.h>

// sigaction()
# include <signal.h>

// perror()
# include <stdio.h>

// exit()
// free()
# include <stdlib.h>

// waitpid()
// WEXITSTATUS()
// WIFEXITED()
# include <sys/wait.h>

// chdir()
// close()
// dup2()
// execve()
// fork()
// getcwd()
// pipe()
// unlink()
// write()
# include <unistd.h>

# include "libft.h"
# include "defines.h"
# include "structs.h"
# include "functions.h"

#endif
