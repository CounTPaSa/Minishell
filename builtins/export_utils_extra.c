/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:02:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/25 17:22:21 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *fill_name(t_command *command, int i, int j, int equal, t_block *block)
{
    char *name;
 
    name = ft_substr(command->args[i], 0, j + 1);
    if (equal == 1 && !command->args[i][j + 1] &&
             (!ft_strncmp(name, command->args[i], j)) == 0)
        return (getchar(), ft_substr(command->args[i], 0, j + 1));
    else
        return (my_malloc(block, name), ft_substr(command->args[i], 0, j));
}

char *fill_content(t_command *command, int i, int j, int equal, t_block *block)
{
    char *content;

     if (equal == 1 && !command->args[i][j + 1])
        content = ft_strdup("");
    else
        content = ft_substr(command->args[i], j + 1, ft_strlen(command->args[i]) - j);
    my_malloc(block, content);
    return (content);
}
