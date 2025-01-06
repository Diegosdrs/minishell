/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_code.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:12:25 by artberna          #+#    #+#             */
/*   Updated: 2024/10/30 10:00:22 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_exit_code(int status, t_gdata *data)
{
	if (WIFEXITED(status))
	{
		g_sig_code = 0;
		data->exit_code = WEXITSTATUS(status);
		return (data->exit_code);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			g_sig_code = SIGINT + SIGOFFSET;
			data->exit_code = g_sig_code;
			return (g_sig_code);
		}
		g_sig_code = SIGOFFSET + WTERMSIG(status);
		data->exit_code = g_sig_code;
		return (g_sig_code);
	}
	return (-1);
}
