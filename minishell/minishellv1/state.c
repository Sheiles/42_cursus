/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sheiles <sheiles@student.42luxembourg.l    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 20:44:07 by sheiles           #+#    #+#             */
/*   Updated: 2025/08/08 21:16:04 by sheiles          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*ms_ctx(t_shell *set)
{
	static t_shell *ctx;

	if (set != NULL)
		ctx = set;
	return (ctx);
}
