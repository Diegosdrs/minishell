/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_II.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 14:57:39 by artberna          #+#    #+#             */
/*   Updated: 2024/10/30 10:33:52 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*end_extract(char *to_find, char *to_ret, t_gdata *data)
{
	char	*var;

	var = NULL;
	var = ft_getenv(&data->s_env, to_find, data);
	if (!var)
		to_ret = ft_strdup("");
	else
		to_ret = ft_strdup(var);
	if (to_find)
		free(to_find);
	return (to_ret);
}

static char	*extract_n_replace_case(t_gdata *data, char *s, int start, int *i)
{
	char	*to_find;
	char	*to_ret;

	to_ret = NULL;
	if (s[(*i)++] == '?' && data->exit_code >= 0)
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
		to_find = ft_substr(s, start, *i - start);
	if (!to_find)
		return (NULL);
	return (end_extract(to_find, to_ret, data));
}

static char	*handle_zero(char *s, int start, int *i)
{
	char	*if_zero;
	char	*to_ret;

	if (s[start] == '0' && (s[start + 1] == '\0'))
		return ((*i)++, ft_strdup("minishell"));
	if_zero = ft_substr(s, start + 1, *i - start - 1);
	if (!if_zero)
		return (NULL);
	to_ret = ft_strdup("minishell");
	to_ret = ft_strjoin(to_ret, if_zero);
	return (free(if_zero), to_ret);
}

char	*extract_n_replace(char *s, t_gdata *data, int *i)
{
	int		start;

	start = *i + 1;
	(*i)++;
	while (s[*i] && (s[*i] == '_' || ft_isalnum(s[*i]) || s[*i] == '?'))
	{
		if (s[*i] == '$' || s[*i] == '?')
			break ;
		(*i)++;
	}
	if (s[*i] == '\0')
		(*i)--;
	if (s[start] == '0')
		return (handle_zero(s, start, i));
	else
		return (extract_n_replace_case(data, s, start, i));
}
