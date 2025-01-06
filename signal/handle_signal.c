/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:55:05 by artberna          #+#    #+#             */
/*   Updated: 2024/10/30 10:12:57 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_code = SIGINT + SIGOFFSET;
}

static void	handle_sigint_child(int sig)
{
	static int	i;

	(void)sig;
	i = 0;
	write(STDOUT_FILENO, "\n", 1);
	signal(SIGINT, SIG_IGN);
	if (i >= 1)
		write(STDOUT_FILENO, "\n", 1);
	i++;
	g_sig_code = SIGINT + SIGOFFSET;
}

static void	handle_sigquit_child(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
	g_sig_code = SIGQUIT + SIGOFFSET;
}

static void	init_sigint_heredoc(int sig, t_gdata *data)
{
	data->heredoc = 1;
	(void)sig;
	write(STDOUT_FILENO, "^C\n", 3);
	rl_replace_line("", 0);
	rl_redisplay();
	g_sig_code = SIGINT + SIGOFFSET;
	exit(g_sig_code);
}

void	init_signal(int option, t_gdata *data)
{
	(void)data;
	if (option == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (option == 1)
	{
		signal(SIGINT, (void (*)(int))init_sigint_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
	if (option == 2)
	{
		signal(SIGQUIT, handle_sigquit_child);
		signal(SIGINT, handle_sigint_child);
	}
}
