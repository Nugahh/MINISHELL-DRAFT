#include "../LIB/minishell.h"

t_token *create_separator(char *str, int start, int end)
{
	t_token *yo;
	int	x;

	x = 0;
	yo = malloc(sizeof(t_token));
	yo->value = ft_calloc(end + 1, sizeof(char)) ;
	while (x < end)
	{
		yo->value[x] = str[start];
		str++;
		x++;
	}
	yo->value[x] = '\0';
	yo->type = START;
	yo->next = NULL;
	return (yo);
}

void	insert_sep(t_token **head, char *str, int start, int end)
{
	t_token *new;
	t_token *temp;

	new = create_separator(str, start, end);
	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

int    is_separator(char c)
{
    if (c == '>' || c == '<' || c == '|')
		return (1);
    return (0);
}

int    skip_separator(int i, char c1, char c2)
{
    if (c2 && ((c1 == '>' && c2 == '>') || (c1 == '<' && c2 == '<')))
        i += 2;
    else if (c1 == '>' || c1 == '<' || c1 == '|')
        i += 1;
    return (i);
}