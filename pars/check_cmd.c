#include "../minishell.h"

void	single_quote(char *line, int i, t_shell *shell)
{
	int	j;

	j = i;
	while (line[i] != '\0')
	{
		if (line[i] == '\'')
		{
			shell->sq_err = 1;
			i++;
			if (line[i] == '\0')
				break ;
			while (line[i] != '\0')
			{
				if (line[i] == '\'')
				{
					shell->sq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->sq_err == 1)
		set_error(shell, -1);
}

void	double_quote(char *line, int i, t_shell *shell)
{
	int	j;

	while (!shell->err && line[i] != '\0')
	{
		if (line[i] == '\"')
		{
			shell->dq_err = 1;
			i++;
			if (line[i] == '\0')
				break ;
			j = i;
			while (line[i] != '\0')
			{
				if (line[i] == '\"')
				{
					shell->dq_err = 0;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	if (shell->dq_err == 1 && shell->sq_err == 0)
		set_error(shell, -2);
}

int	pipe_syntax(char *line, int i, t_shell *shell)
{
	while (!shell->err && line[i] != '\0')
	{
		if (line[i] == '|')
		{
			shell->flags.pipe_count++;
			i++;
			i = space_skip(line, i);
			if (ft_strchr("|", line[i]))
			{
				set_error(shell, -3);
				return (-1);
			}
		}
		if (line[i] == '\"')
			while (line[++i] != '\"')
				;
		if (line[i] == '\'')
			while (line[++i] != '\'')
				;
		i++;
	}
	return (0);
}

int	redir_syntax(char *line, int i, t_shell *shell)
{
	while (!shell->err && line[i] != '\0')
	{
		if (ft_strchr("><", line[i]))
		{
			i++;
			if (ft_strchr("|><", line[i]) && line[i])
				i++;
			i = space_skip(line, i);
			if (ft_strchr("|><", line[i]))
			{
				set_error(shell, -4);
				return (-1);
			}
		}
		if (line[i] == '\"')
		{
			while (line[++i] != '\"')
				;
		}
		if (line[i] == '\'')
			while (line[++i] != '\'')
				;
		i++;
	}
	return (0);
}
