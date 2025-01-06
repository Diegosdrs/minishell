/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar_hdoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:35:43 by artberna          #+#    #+#             */
/*   Updated: 2024/10/29 11:37:01 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static char	*copy_str_hdoc(char *str, char c)
{
	int		len;
	char	*new_str;

	if (!str)
		str = ft_strdup("");
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	new_str = ft_realloc(str, len, len + 2);
	if (!new_str)
		return (free(str), NULL);
	new_str[len] = c;
	new_str[len + 1] = '\0';
	return (new_str);
}

static char	*extract_n_replace_hdoc(char *s, t_gdata *data, int *i)
{
	int		start;

	start = *i + 1;
	(*i)++;
	while (s[*i] && (s[*i] == '_' || ft_isalnum(s[*i])))
	{
		if (s[*i] == '\'' || s[*i] == '\"' || s[*i] == '$' || s[*i] == '?')
			break ;
		(*i)++;
	}
	if (s[*i] == '\0')
		(*i)--;
	if (s[start] == '0')
		return (handle_zero(s, start, i));
	else
		return (extr_n_repl_case_hdoc(data, s, start, i));
}

static char	*make_var_hdoc(char *s, t_gdata *data, int *i, char *result)
{
	char	*tmp;
	char	*new_res;
	int		res_len;

	tmp = extract_n_replace_hdoc(s, data, i);
	if (!tmp)
		return (free(result), NULL);
	res_len = ft_strlen(result) + ft_strlen(tmp);
	new_res = ft_calloc(res_len + 2, sizeof(char));
	if (!new_res)
	{
		if (result)
			free(result);
		if (tmp)
			free(tmp);
		return (NULL);
	}
	ft_strcpy(new_res, result);
	ft_strcat(new_res, tmp);
	if (result)
		free(result);
	if (tmp)
		free(tmp);
	return (new_res);
}

char	*replace_dollar_hdoc(char *s, t_gdata *data)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '$')
		{
			result = make_var_hdoc(s, data, &i, result);
			if (!result)
				return (NULL);
		}
		else
		{
			result = copy_str_hdoc(result, s[i++]);
			if (!result)
				return (NULL);
		}
	}
	return (result);
}
