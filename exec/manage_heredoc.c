/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 09:14:21 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/30 10:54:38 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	manage_hdoc(t_cmds *cmds, int i)
{
	t_cmds	*temp;
	pid_t	pid;
	int		status;

	temp = cmds;
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		while (temp != NULL)
		{
			if (is_it_heredoc(temp) == 1)
				create_hdoc_file(temp, create_file_name(i));
			temp = temp->next;
			i++;
		}
		exit(EXIT_SUCCESS);
	}
	waitpid(pid, &status, 0);
	g_sig_code = get_exit_code(status, cmds->g_data);
	if (g_sig_code == 130)
		return (g_sig_code);
	return (affect_heredoc_name(cmds));
}

const char	*create_file_name(int i)
{
	char		*str;
	const char	*str_2;

	str = ft_itoa(i);
	str_2 = ft_strjoin_no_free("/tmp/HDOC_FILE", str);
	free(str);
	return (str_2);
}

void	create_hdoc_file(t_cmds *cmds, const char *str)
{
	int		fd;
	char	*line;
	t_token	*temp_tok;

	init_signal(1, cmds->g_data);
	line = NULL;
	temp_tok = cmds->redir;
	while (temp_tok != NULL)
	{
		if (temp_tok->type == TOK_HDOC)
		{
			fd = open(str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd < 0)
				ft_error("Failed to open HDOC_FILE", cmds, 1);
			while (1)
			{
				if (input_heredoc(temp_tok, line, fd, cmds->g_data) == 0 \
				|| cmds->g_data->heredoc == 1)
					break ;
			}
			close (fd);
		}
		temp_tok = temp_tok->next;
	}
}

int	input_heredoc(t_token *temp_tok, char *line, int fd, t_gdata *data)
{
	char	*tmp;

	tmp = NULL;
	line = readline("> ");
	if (line == NULL || ft_strncmp(line, temp_tok->token,
			(ft_strlen(line) + ft_strlen(temp_tok->token))) == 0)
	{
		if (line == NULL)
			ft_putstr_fd("minishell: warning: heredoc: called end-of-line\n", 2);
		free(line);
		return (0);
	}
	if (ft_strstr(line, "$"))
	{
		(void)data;
		tmp = replace_dollar_hdoc(line, data);
		line = tmp;
		free(line);
	}
	ft_putstr_fd(line, fd);
	ft_putstr_fd("\n", fd);
	free(line);
	return (1);
}
