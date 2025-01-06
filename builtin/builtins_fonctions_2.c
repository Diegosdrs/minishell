/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_fonctions_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artberna <artberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:49:16 by dsindres          #+#    #+#             */
/*   Updated: 2024/10/30 11:12:30 by artberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n(char *cmd)
{
	int	i;

	i = 1;
	if (cmd[0] != '-')
		return (1);
	if (cmd[1] != 'n')
		return (1);
	while (cmd[i])
	{
		if (cmd[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}
