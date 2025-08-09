/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/09 16:50:27 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/09 16:50:31 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_mini *ms, char **cmd)
{
	char	new_line;
	int		i;
	int		j;

	new_line = 1;
	i = 1;
	while (cmd && cmd[i] && !ft_strncmp (cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j] == 'n')
			j++;
		if (cmd[i][j] != '\0')
			break ;
		new_line = 0;
		i++;
	}
	while (cmd && cmd[i])
	{
		ft_printf ("%s", cmd[i]);
		if (cmd[++i])
			ft_putchar_fd (' ', 1);
	}
	if (new_line)
		ft_printf ("\n");
	ms -> error = 0;
}
