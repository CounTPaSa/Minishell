/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:18:18 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/28 15:29:56 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

// PWD OLUTIUR KANKANSSSS (silmeyi unutma)

static int _home(t_mshell *shell)
{
    char    *home;
    
    home = find_env(shell, "HOME");
    if (ft_strcmp(home, "") == 0)
        return (*exit_status() = 1, printf("cd: HOME not set\n"), 1);
    if (chdir(home) == -1)
        return (*exit_status() = 1,
                 printf("cd: %s: No such file or directory\n", home), 1);
    return (0);
}

static int find_env_cd(t_mshell *shell, char *path)
{
    t_env *search_env;

    search_env = shell->env;
    while(search_env != NULL)
    {

        if((ft_strncmp(search_env->name, path, ft_strlen(search_env->name)) == 0) && (ft_strncmp(search_env->name, path, ft_strlen(path)) == 0))
            return(1);
        search_env = search_env->next;
    }
    return(0);
}

int cd(t_command *command, t_mshell *shell)
{
    char cwd[1024];
    char *pwd;
    char *path = NULL;

    *exit_status() = 0;
    pwd = find_env(shell, "PWD");
    if (command->args[1])
        path = command->args[1];
    else if (_home(shell) == 0)
        path = find_env(shell, "HOME");
    else
        return (1);
    if (chdir(path) == -1 && ft_strcmp(path, "") != 0)
       return (*exit_status() = 1,
        printf("cd: %s: No such file or directory\n", path), 1);
    else
        chdir(path);
    change_env(shell, "OLDPWD", pwd);
    pwd = getcwd(cwd, sizeof(cwd));
    if (!pwd)
        return (*exit_status() = 1, perror("getcwd"), 1);
    if (find_env_cd(shell, "PWD"))
        change_env(shell, "PWD", pwd);
    else
    {
        printf("PWD not found %s\n", pwd);
        ft_lstadd_back_env(&shell->env, ft_lstnew_env("PWD", pwd));
    }
    return (0);
}
