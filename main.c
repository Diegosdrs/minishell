/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:45:49 by artberna          #+#    #+#             */
/*   Updated: 2024/10/30 10:16:34 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_code = 0;

void	free_minishell(t_cmds *cmd, t_token *tok, char *input)
{
	if (cmd)
		free_cmd(cmd);
	if (tok)
		free_token(tok);
	if (input)
		free(input);
	rl_on_new_line();
}

static void	minishell(t_gdata *data, t_token *tok, t_cmds *cmd)
{
	while (1)
	{
		init_signal(0, data);
		data->input = readline("minishell ~ ");
		if (!data->input)
			return ;
		add_history(data->input);
		tok = lexer(data);
		data->s_tok = tok;
		if (error_handler(&tok, data))
			continue ;
		cmd = parser(tok, data);
		minishell_exec(cmd, data);
		free_minishell(cmd, tok, data->input);
	}
}

int	main(int ac, char **av, char **env)
{
	t_gdata	data;
	t_token	*tok;
	t_cmds	*cmd;

	(void)ac, (void)av;
	tok = NULL;
	cmd = NULL;
	if (init_struct_env(env, &data.s_env))
		return (EXIT_FAILURE);
	data.exit_code = 0;
	minishell(&data, tok, cmd);
	clear_history();
	free_double(data.s_env.tab_env);
	if (data.s_env.oldpwd != NULL)
		free (data.s_env.oldpwd);
	ft_putstr_fd("exit\n", 2);
	return (0);
}
