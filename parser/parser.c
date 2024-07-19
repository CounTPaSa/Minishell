/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:47:24 by merboyac          #+#    #+#             */
/*   Updated: 2024/07/17 22:32:26 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <./readline/history.h>
#include <./readline/readline.h>

// echo "jvdfn" "frıfer" bu iki string arasında bir boşluk olmalı

static void file_creation(t_mshell *shell, t_redirection *redirection, t_lexer **lexer)
{
    if((*lexer)->type == TOKEN_REDIR_APPEND && (*lexer)->next != NULL)
    {
        (*lexer) = (*lexer)->next;
        expander(shell, (*lexer));
        unquote_the_output((*lexer));
        redirection->redir_fd = open((*lexer)->content,O_CREAT | O_RDWR | O_APPEND, 0777);
        if(redirection->redir_fd == -1)
            return(perror((*lexer)->content));
    }
    else if((*lexer)->type == TOKEN_REDIR_IN && (*lexer)->next != NULL)
    {
        (*lexer) = (*lexer)->next;
        redirection->redir_fd = open((*lexer)->content,O_CREAT , 0777);
        if(redirection->redir_fd == -1)
            return(perror((*lexer)->content));
    }
    else if ((*lexer)->type == TOKEN_REDIR_OUT && (*lexer)->next != NULL)
    {
        (*lexer) = (*lexer)->next;
        expander(shell, (*lexer));
        unquote_the_output((*lexer));
        redirection->redir_fd = open((*lexer)->content,O_CREAT | O_RDWR | O_TRUNC, 0777);
        if(redirection->redir_fd == -1)
            return(perror((*lexer)->content));
    }
}

void redirection(t_mshell *shell,t_command **command, t_lexer **lexer)
{
    int index;

    index = 0;
    while((*lexer) != NULL && (*lexer)->type != TOKEN_WORD && (*lexer)->type != TOKEN_PIPE)
    {
        if ((*lexer)->type == TOKEN_HEREDOC && (*lexer)->next != NULL)
        {
            (*lexer) = (*lexer)->next;
            heredoc_start(shell ,&(*command)->redirection[index],(*lexer)->content);
        }
      else
            file_creation(shell ,&(*command)->redirection[index], &(*lexer));
        if((*lexer)->next != NULL)
            (*lexer) = (*lexer)->next;
        else if(&(*command)->redirection[index + 1])
                index++;
    }
}

void parser_start(t_mshell *shell,t_command *command, t_lexer *lexer)
{
    int index;

    index = 0;
    while(lexer != NULL && command != NULL)
    {
        if(lexer->type == TOKEN_WORD)
        {
            expander(shell, lexer);
            unquote_the_output(lexer);
            shell->command->args[index] = lexer->content;
            if(shell->command->args[index + 1])
                    index++;
            printf("%s\n", shell->command->args[index]);
        }
        if(lexer->type == TOKEN_PIPE)
        {
            index = 0;
            pipe(command->pipe_fd);
            command = command->next;
        }
        if(lexer->type != TOKEN_WORD && lexer->type != TOKEN_PIPE)
            redirection(shell ,&shell->command, &lexer);
        lexer = lexer->next;
    }
    // pipe açılırken status düşünülecek
}

void parser(t_mshell *shell)
{
    t_lexer *lexer;

    lexer = shell->lexer;
    while(lexer != NULL)
    {
        parser_init(shell, &lexer);
        lexer = lexer->next;
    }
    parser_start(shell,shell->command, shell->lexer);
}
