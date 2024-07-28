/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 15:29:15 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/28 13:23:23 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void if_not_exist(t_mshell *shell, t_env *env, char *name, char *content)
{
    env = ft_lstnew_env(name, content);
    if (!env)
        return ;
    ft_lstadd_back_env(&shell->env, env);
}

int id_validation(char *command)
{
    int i;

    i = 0;
    if (command[0] == '_' && command[1] == '\0')
        return (FALSE);
    if (ft_isalpha(command[i]) == 0 && command[i] != '_')
        return (printf("export: `%s': not a valid identifier\n",command),
            *exit_status() = 1, FALSE);
    i++;
    while (command[i] && command[i] != '=')
    {
        if (ft_isalnum(command[i]) == 0 && command[i] != '_' && command[i] != '=')
        {
                printf("export: `%s': not a valid identifier\n", command);
            return (*exit_status() = 1 ,FALSE);
        }
        i++;
    }
    return (TRUE);
}
