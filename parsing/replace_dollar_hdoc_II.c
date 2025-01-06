/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_hdoc_II.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:54:37 by artberna          #+#    #+#             */
/*   Updated: 2024/10/30 10:40:04 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*switch_case_hdoc(t_gdata *data, char *s, int start, int *i)
{
	char	*var;
	char	*to_find;
	char	*to_ret;

	if (s[*i - 1] == '\'' || s[*i - 1] == '\"')
		to_find = ft_substr(s, start, (*i)-- - start - 1);
	else
		to_find = ft_substr(s, start, *i - start);
	if (!to_find)
		return (NULL);
	var = ft_getenv(&data->s_env, to_find, data);
	if (var)
		to_ret = ft_strdup(var);
	else
		to_ret = ft_strdup("");
	return (free(to_find), to_ret);
}

char	*extr_n_repl_case_hdoc(t_gdata *data, char *s, int start, int *i)
{
	char	*to_find;
	char	*to_ret;

	to_ret = NULL;
	if (s[(*i)++] == '?' && data->exit_code)
		return (ft_itoa(data->exit_code));
	else if (ft_isdigit(s[start]))
	{
		to_find = ft_substr(s, start + 1, *i - start - 1);
		if (!to_find)
			return (NULL);
		to_ret = ft_strdup(to_find);
		return (free(to_find), to_ret);
	}
	else
		return (switch_case_hdoc(data, s, start, i));
}
