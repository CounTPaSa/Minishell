/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: merboyac <muheren2004@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:06:30 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/28 18:48:19 by merboyac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int skip_ws(char c)
{
    if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r')
        return (1);
    return (0);
}

static void exit_with_err(t_mshell *shell)
{
    ft_putstr_fd("exit\n", 2);
    ft_putstr_fd("minishell: exit: ", 2);
    ft_putstr_fd(shell->command->args[1], 2);
    ft_putstr_fd(": numeric argument required\n", 2);
    end_malloc(shell);
    exit(255);
}

static void set_flag_exit(t_mshell *shell, t_command *command)
{
    int rtn;
    int i;

    i = 0;
    while (skip_ws(command->args[1][i]))
        i++;    
    if (command->args[1][i] == '-'
        || command->args[1][i] == '+')
        i++;
    while (command->args[1][i])
    {
        if (ft_isdigit(command->args[1][i]) == 0)
            exit_with_err(shell);
        i++;
    }
    rtn = ft_atoi(command->args[1]);
    ft_putstr_fd("exit\n", 1);
    end_malloc(shell);
    *exit_status() = (256 + rtn) % 256;
    exit(*exit_status());
}

int get_cmd_count(t_command *command)
{
    int count;
    int i;

    i = 0;
    count = -1;
    while (command && command->args[i])
    {
        count++;
        i++;
    }
    
    return (count);
}

void ft_exit(t_mshell *shell, t_command *command)
{  
    int cmd_count;

    cmd_count = get_cmd_count(command);

    if (cmd_count == 0)
    {
        ft_putstr_fd("exit\n", 1);
        end_malloc(shell);
        *exit_status() = 0;
        exit(0);
    }
    if (cmd_count > 1)
    {
        ft_putstr_fd("exit\n", 2);
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        return ;
    }
    if (command->args && command->args[1])
    {
        printf("command->args[1]: %s\n", command->args[1]);
        set_flag_exit(shell, command);
        return ;
    }
}