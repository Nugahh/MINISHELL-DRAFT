#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../LIB/minishell.h"

int	ft_strlen(const char *s)
{
	int	a;

	a = 0;
	while (s[a])
	{
		a++;
	}
	return (a);
}

char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		i;
	int		j;

	i = 0;
	while (s1[i])
		i++;
	copy = malloc(sizeof(char) * i + 1);
	if (!copy)
		return (0);
	j = 0;
	while (j < i)
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

#include <stdlib.h>
#include <stddef.h>

static int	ft_count_words(char const *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_putword(char *word, char const *s, int i, int word_len)
{
	int	j;

	j = 0;
	while (word_len > 0)
	{
		word[j] = s[i - word_len];
		j++;
		word_len--;
	}
	word[j] = '\0';
	return (word);
}

static char	**ft_split_words(char const *s, char c, char **s2, int num_words)
{
	int	i;
	int	word;
	int	word_len;

	i = 0;
	word = 0;
	word_len = 0;
	while (word < num_words)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			word_len++;
		}
		s2[word] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!s2)
			return (0);
		ft_putword(s2[word], s, i, word_len);
		word_len = 0;
		word++;
	}
	s2[word] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num_words;

	if (!s)
		return (0);
	num_words = ft_count_words(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num_words + 1));
	if (!s2)
		return (0);
	ft_split_words(s, c, s2, num_words);
	return (s2);
}

void	fill_cmd_test(t_cmdexec **head)
{
	t_cmdexec	*temp;

	temp = *head;
	temp = malloc(sizeof(t_cmdexec));
	temp->arg = ft_strdup("ls");
	temp->red = NULL;
	temp->fd_in = 0;
	temp->fd_out = 1;
	temp->next = NULL;
}

char	*path_cat(char *path, t_cmdexec **head)
{
	char	*full_path;
	int		i;
	int		j;
	t_cmdexec	*temp;

	i = -1;
	j = 0;
	temp = *head;
	full_path = malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(temp->arg) + 2));
	if (!full_path)
		return (NULL);
	while (path[++i])
		full_path[++i] = path[++i];
	full_path[i] = '/';
	i++;
	while (temp->arg[j])
	{
		full_path[i] = temp->arg[j];
		i++;
		j++;
	}
	full_path[i] = '\0';
	return (full_path);
}

char	*access_check(t_cmdexec **head, int i)
{
	char	*path;
	char	*full_path;
	char	**path_split;
	t_cmdexec	*temp;

	temp = *head;
	path = getenv("PATH");
	path_split = ft_split(path, ':');
	while(path_split[i])
	{
		full_path = path_cat(path_split[i], &temp);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		else
			free(full_path);
		i++;
	}
	return (free(path_split), NULL);
}

void execute_command(t_cmdexec **head)
{
    char *path;
	t_cmdexec	*temp;
    
	temp = *head;
    path = access_check(&temp, 0);
    if (path) 
	{
        if (execve(path, (char * const*)temp->arg, NULL) == -1) 
		{
            printf("Error: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
        free(path);
    } 
	else 
	{
        printf("Command does not exist or is not executable.\n");
        exit(EXIT_FAILURE);
    }
}

int main() 
{
	t_cmdexec	*head;

	head = NULL;
	fill_cmd_test(&head);
	execute_command(&head);
	return (0);
}
