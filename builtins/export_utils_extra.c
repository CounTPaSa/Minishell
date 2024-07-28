/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_extra.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 14:02:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/28 17:19:56 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *fill_name(t_command *command, int i, int j, int equal)
{
    char *name;
 
    name = ft_substr(command->args[i], 0, j + 1);
    if (equal == 1 && !command->args[i][j + 1] &&
             (!ft_strncmp(name, command->args[i], j)) == 0)
        return (free(name), ft_substr(command->args[i], 0, j + 1));
    else
        return (free(name), ft_substr(command->args[i], 0, j));
}

char *fill_content(t_command *command, int i, int j, int equal)
{
    char *content;

     if (equal == 1 && !command->args[i][j + 1])
        content = ft_strdup("");
    else if (equal == 1 && command->args[i][j + 1])
        content = ft_substr(command->args[i], j + 1, ft_strlen(command->args[i]) - j);
	else
		content = NULL;
    return (content);
}

void sort_env_list(t_env *head) 
{
    if (head == NULL)
        return;

    int swapped = 1;
    t_env *ptr1;
    t_env *lptr = NULL;

    while (swapped) {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ft_strncmp(ptr1->name, ptr1->next->name, ft_strlen(ptr1->name) + 1) > 0) 
			{
                char *temp_name = ptr1->name;
                char *temp_content = ptr1->content;
                ptr1->name = ptr1->next->name;
                ptr1->content = ptr1->next->content;
                ptr1->next->name = temp_name;
                ptr1->next->content = temp_content;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
}

 void	only_export(t_env *env)
{ 
		t_env *tmp;
		
		tmp = env;
		sort_env_list(tmp);
	    while (tmp && tmp->name[0])
	    {
			if (!(tmp->name[0] == '_' && tmp->name[1] == '\0'))
			{
	    		ft_putstr_fd("declare -x ", 1);
	    		ft_putstr_fd(tmp->name, 1);
				if (!tmp->content)
				{
					ft_putstr_fd("\n", 1);
					tmp = tmp->next;
					continue;
				}	
	    		if (tmp->content && tmp->content[0] == '\0')
	    		{
	    			ft_putstr_fd("=\"", 1);
	    			ft_putstr_fd("\"", 1);
	    		}
	    		if (tmp->content && tmp->content[0] != '\0')
	    		{
	    			ft_putstr_fd("=\"", 1);
	    			ft_putstr_fd(tmp->content, 1);
	    			ft_putstr_fd("\"", 1);
	    		}
	    		ft_putstr_fd("\n", 1);
			}
	    	tmp = tmp->next;
	    }
}
