/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 11:14:21 by artberna          #+#    #+#             */
/*   Updated: 2024/10/30 10:13:15 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmds *cmd)
{
	t_cmds	*tmp;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->cmd)
			free_double(tmp->cmd);
		if (tmp->redir)
			free_token(tmp->redir);
		free(tmp);
	}
}

int	is_redir(t_token_type type)
{
	if (type == TOK_APP || type == TOK_IR || \
		type == TOK_OR || type == TOK_HDOC)
		return (1);
	return (0);
}

int	is_cmd(t_token_type type)
{
	if (type == TOK_S_Q || type == TOK_D_Q || \
		type == TOK_STR)
		return (1);
	return (0);
}

static t_cmds	*create_node(t_gdata *data)
{
	t_cmds	*new;

	new = ft_calloc(sizeof(t_cmds), 1);
	ft_memset(new, 0, sizeof(t_cmds));
	new->cmd = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->redir = NULL;
	new->g_data = data;
	return (new);
}

void	extend_cmd(t_cmds **cmd, t_gdata *data)
{
	(*cmd)->next = create_node(data);
	(*cmd)->next->prev = *cmd;
	(*cmd)->next->index = (*cmd)->index + 1;
	(*cmd)->next->flag_error = 0;
	*cmd = (*cmd)->next;
	data->nb_command++;
}
