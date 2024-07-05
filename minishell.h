/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: onurgokkaya <onurgokkaya@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:39:51 by ogokkaya          #+#    #+#             */
/*   Updated: 2024/07/04 21:15:13 by onurgokkaya      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"

# define TRUE 0
# define FALSE 1

// LEXER_DEFINES
# define SPACE ' '
# define PIPE '|'
# define BRACKET_OPEN '('
# define BRACKET_CLOSE ')'
# define REDIRECT_OUT '>'
# define REDIRECT_IN '<'
# define SINGLE_QUOTE '\''
# define DOUBLE_QUOTE '\"'

// PRINT_DEFINES
# define PROMT "minishell$"
//ERROR
# define MALLOC "Error\nCould not allocate memory\n"
#define ARG "Error\nThe program can only run without arguments\n"

typedef enum s_token_type
{
	TOKEN_PIPE = 1,
	TOKEN_REDIRECT,
	TOKEN_HEREDOC,
	TOKEN_COMMAND
}	t_token_type;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;


typedef struct s_lexer
{
	char *content;
	t_token_type type;
	struct s_lexer *next;
}			t_lexer;

typedef struct s_block
{
	void			*allocate;
	struct s_block	*next;
}					t_block;

typedef struct s_mshell
{
	char			*input;
	struct s_block	*block;
	struct s_lexer  *lexer;
	struct s_env	*env;
}					t_mshell;

// input_control
int			line_verify(char *line);
int			ft_space(char c);


// memory monitor
void				*my_malloc(t_block *block, void *address);
void				free_malloc(t_block *block, void *delete_adress);
void				ft_lstdelone_memory(t_block *lst, void (*del)(void *));
void				end_malloc(t_mshell *shell);
t_block				*ft_lstnew_memory(void *content);
void				ft_lstadd_back_memory(t_block **lst, t_block *new);
void				ft_lstclear_memory(t_block **lst, void (*del)(void *));
t_block				*malloc_starter(void);

// error handling
void				error_exit(char *error_message, t_mshell *shell,
						int free_flag);

// env
t_env				*ft_lstnew_env(char *str, char *ptr);
void				ft_lstadd_back_env(t_env **lst, t_env *new);
int					get_env(char **env, t_mshell *shell);
void				free_env(t_mshell *shell);

// lexer
void 		lexer(t_mshell *shell);
t_lexer	*ft_lstnew_lexer(t_mshell *shell ,char *content, t_token_type type);
void	ft_lstadd_back_lexer(t_lexer **lst, t_lexer *new);

//expander
void expender(t_mshell *shell);


#endif