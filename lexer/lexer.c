/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ogokkaya <ogokkaya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 13:53:37 by merboyac          #+#    #+#             */
/*   Updated: 2024/08/07 18:11:14 by ogokkaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../minishell.h"
#include <stdio.h>

static int	skip_quoted_section(const char *input, int i)
{
	char	quote;

	quote = input[i++];
	while (input[i] && input[i] != quote)
		i++;
	return (i);
}

static int	get_next_token_length(char *input)
{
	int	i;

	i = 0;
	if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i
				+ 1] == '>'))
		return (2);
	if (input[i] && (input[i] == '>' || input[i] == '<' || input[i] == '|'))
		return (1);
	while (input[i] && input[i] != '>' && input[i] != '<' && input[i] != '|'
		&& input[i] != ' ')
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			i = skip_quoted_section(input, i) + 1;
			if (!input[i])
				break ;
		}
		else
			i++;
	}
	return (i);
}

static t_token_type	determine_token_type(char *token)
{
	if (ft_strncmp(token, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	if (ft_strncmp(token, ">>", 2) == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strncmp(token, "<", 1) == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strncmp(token, ">", 1) == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(token, "|") == 0)
		return (TOKEN_PIPE);
	return (TOKEN_WORD);
}

static void	parse_command_tokens(char *input, t_mshell *shell)
{
	int				len;
	char			*content;
	t_token_type	type;
	char			*next_input_tmp;

	while (input && *input)
	{
		len = get_next_token_length(input);
		if (len == 0)
			break ;
		content = ft_substr(input, 0, len);
		if (my_malloc(shell->block, content))
			return (end_malloc(shell), exit(EXIT_FAILURE));
		type = determine_token_type(content);
		ft_lstadd_back_lexer(&shell->lexer, ft_lstnew_lexer(shell, content,
				type));
		next_input_tmp = ft_strtrim(input + len, " ");
		if (my_malloc(shell->block, next_input_tmp))
			return (perror("next_input_tmp"), end_malloc(shell),
				exit(EXIT_FAILURE));
		input = next_input_tmp;
	}
}

void	lexer(t_mshell *shell)
{
	char	*input_tmp;

	input_tmp = ft_strtrim(shell->input, " ");
	if (my_malloc(shell->block, input_tmp))
		return (perror("input_tmp"), end_malloc(shell), exit(EXIT_FAILURE));
	parse_command_tokens(input_tmp, shell);
}
