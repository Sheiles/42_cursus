/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:49:53 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 17:00:19 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# ifndef ERROR_MSG
// #  define ERROR_MSG "\033[1;31mERROR\n\033[0m"
#  define ERROR_MSG ""
# endif

# ifndef EXIT_MSG
// #  define EXIT_MSG "\033[1;35mSee you soon, human!\033[0m"
#  define EXIT_MSG ""
# endif

# ifndef PROMPT_MSG
#  define PROMPT_MSG "minishell"
# endif

# ifndef INVALID_USAGE
#  define INVALID_USAGE "invalid usage"
# endif

# ifndef SEP
#  define SEP -1
# endif

enum e_type
{
	PIPE = 10,
	EXECVE = 11,
	BUILDIN = 12,
	ARG = 13,
	ARG_FILE = 14,
	REDIRECT = 15,
	HEREDOC = 16
};

#endif
