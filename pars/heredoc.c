#include "../minishell.h"

int	heredoc_comp(t_shell *shell, char *stop)
{
	struct s_process	*new;
	char				*file;

	if (!shell->err)
	{
		file = ft_itoa(++shell->mem);
		if (heredoc_test(shell, stop, file))
		{
			new = (struct s_process *)ft_calloc(1, sizeof(*new));
			if (new == NULL)
				return (set_error(shell, -5));
			new->args = (char **)ft_calloc(2, sizeof(char *));
			if (new->args == NULL)
				return (set_error(shell, -5));
			new->status |= (BUILTIN | HEREDOC);
			new->args[0] = file;
			shell->flags.pipe_count++;
			shell->flags.pipe_out = shell->flags.pipe_in + 1;
			set_flags(new, shell);
			shell->flags.pipe_out++;
			ft_lstadd_back(&shell->cmd, ft_lstnew(new));
		}
	}
	shell->flags.heredoc = 0;
	return (1);
}

int	heredoc_init(t_shell *shell, char *stop)
{
	shell->flags.heredoc = 1;
	shell->flags.double_q = 1;
	heredoc_comp(shell, stop);
	return (1);
}

void	heredoc_read(t_shell *shell, char *stop, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, stop) == 0)
			break ;
		check_for_env(&line, shell);
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		if (line)
			free(line);
	}
	if (line)
		free(line);
}

int	heredoc_test(t_shell *shell, char *stop, char *filename)
{
	int		pid;
	int		status;

	((pid = fork()) == -1) && err("fork failed");
	if (pid == CHILD_PID)
	{
		signal(SIGINT, SIG_DFL);
		shell->h_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		heredoc_read(shell, stop, shell->h_fd);
		close(shell->h_fd);
		exit(0);
	}
	else
	{
		waitpid(0, &status, 0);
		if (status)
		{
			if (WIFSIGNALED(status))
				set_error(shell, -6);
			unlink(filename);
			free(filename);
			return (0);
		}
	}
	return (1);
}
