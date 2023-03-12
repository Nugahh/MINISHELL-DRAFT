#include "../LIB/minishell.h"

void	delete_token(t_token *toDel)
{
	t_token **head;
	t_token	*temp;
	t_token	*prev;

	temp = *head;
	prev = NULL;
	while (temp && temp != toDel)
	{
		prev = temp;
		temp = temp->next;
	}
	if (toDel->next == NULL)
	{
		free(toDel);
		if (prev == NULL)
			return ;
		prev->next = NULL;
		return ;
	}
	toDel->value = temp->next->value;
	toDel->type = temp->next->type;
	temp->next = temp->next->next;
	free(temp->next);
}
char	*find_var_name(t_token *token, int *i)
{
	t_token	*temp;
	char	*copy;
	int		len;
	int		j;

	temp = token;
	len = len_env(temp->value, *i);
	copy = ft_calloc(len + 1, sizeof(char));
	while (is_allowed_char(temp->value[*i]) == 1)
		copy[j++] = temp->value[*i++];
	return (copy);
}

char	*copy_before_expand(t_token *token, int *i)
{
	t_token	*temp;
	char 	*copy;
	int		j;

	temp = token;
	j = 0;
	while (j < *i)
		j++;
	if (j > 0)
	{
		copy = ft_calloc(j + 1, sizeof(char));
		copy = ft_strncpy(copy, temp->value, j);
		return (copy);
	}
	return (NULL);
}

char	*copy_after_expand(t_token *token, int *i, char *copyVar)
{
	char	*copy;
	int		j;
	int		len;

	j = 0;
	len = len_rest_of_token(token, *i) - ft_strlen(copyVar);
	copy = ft_calloc(len + 1, sizeof(char));
	while (token->value[*i])
	{
		copy[j] = token->value[*i];
		j++;
		i++;
	}
	return (copy);
}

char	*env_expanded(t_env **env, char *copyVar)
{
	t_env	*tempEnv;
	char	*copyEnv;
	int		len;
	int		i;

	tempEnv = *env;
	copyEnv = NULL;
	i = -1;
	while (tempEnv)
	{
		len = ft_strlen(tempEnv->value);
		if (ft_strncmp(tempEnv->name, copyVar, ft_strlen(tempEnv->name)) == 0)
		{
			copyEnv = ft_calloc(len + 1, sizeof(char));
			while (tempEnv->value[++i])
				copyEnv[i] = tempEnv->value[i];
			return (copyEnv);
		}
		tempEnv = tempEnv->next;
	}
	return (NULL);
}

int	len_env_expanded(t_token *temp, t_env **env, char *copyVar)
{
	t_env	*tempEnv;
	char	*copyEnv;
	int		len;
	int		i;

	tempEnv = *env;
	copyEnv = NULL;
	i = 0;
	while (tempEnv)
	{
		len = ft_strlen(tempEnv->value);
		if (ft_strncmp(tempEnv->name, copyVar, ft_strlen(tempEnv->name)) == 0)
		{
			copyEnv = ft_calloc(len + 1, sizeof(char));
			while (tempEnv->value[i])
				i++;
			return (i);
		}
		tempEnv = tempEnv->next;
	}
	len = ft_strlen(copyVar);
	return (len);
}

int	len_copy_before_expand(char *copy, int *i)
{
	int j;

	j = 0;
	while (j < *i)
		j++;
	return (j);
}

int	len_rest_of_token(t_token *token, int *i)
{
	int	len;

	len = 0;
	while (token->value[*i])
	{
		len++;
		*i++;
	}
	return (len);
}

int	len_token(t_token *token)
{
	int	len;

	len = 0;
	while (token->value[len])
		len++;
	return (len);
}

int	ft_join_expand_bef(t_token *token, int *i, char *copyBeforeExpand, char *copyVar)
{
	t_env	**env;
	char	*copy;
	char	*copyEnv;
	char	*firstPart;
	int		lenFirstPart;

	copy = ft_calloc(len_token(token) + 1, sizeof(char));
	copy = ft_strncpy(copy, token->value, ft_strlen(token->value));
	lenFirstPart = ft_strlen(len_env_expanded(token, env, copyVar)) 
				+ len_copy_before_expand(copy, &i) - ft_strlen(copyVar) + 1;
	firstPart = ft_calloc(lenFirstPart + 1, sizeof(char));
	copyEnv = env_expanded(env, copyVar);
	if (copyEnv == NULL)
		return (-1);
	firstPart = ft_strncat(copyEnv, copyBeforeExpand, ft_strlen(copyBeforeExpand));
	free(copyEnv);
	free(copyBeforeExpand);
	return (0);
}

// int	before_expand(t_token *token, t_env *env, int *i, char *copy)
// {
// 	t_token	*temp;
// 	t_env	*tempEnv;
// 	char	*copyVar;
// 	int		j;

// 	temp = token;
// 	tempEnv = env;
// 	j = 0;
// 	if (i > 0)
// 		copy = copy_before_expand(temp, &i);
// 	while (temp->value[*i])
// 	{
// 		if (temp->value[*i] == '$' && is_allowed_char(temp->value[*i + 1]))
// 		{
// 			copyVar = find_var_name(&temp, &i + 1);
// 			if (copyVar == NULL)
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

int	before_expand_def(t_token *token, t_env *env, int *i, char *copy)
{
	char	*copyBefore;
	char	*copyAfter;
	char	*copyVar;
	int		j;

	copyBefore = copy_before_expand(token, *i);
	if (token->value[*i] == '$' && is_allowed_char(token->value[*i + 1]))
	{
		i++;
		copyVar = find_var_name(token, &i + 1);
		if (copyVar == NULL)
			return (1);
		if (ft_join_expand_bef(token, &i, copyBefore, copyVar) == 1)
			return (1);
		else if(ft_join_expand_bef(token, &i, copyBefore, copyVar) == -1)
			
		if (token->value[*i] != '\0')
			copyAfter = copy_after_expand(token, &i, copyVar);
		else
		return (0);
	}
	free(copyBefore);
	return (0);
}

int	expand_def(t_token *token, t_env **env, int *i)
{
	char	*copyVar;
	int		j;
	int		lenToken;

	lenToken = len_token(token);
	copy = ft_calloc(lenToken + 1, sizeof(char));
	copy = ft_strncpy(copy, token->value, ft_strlen(token->value));
	while (token->value[*i] && token->value[*i - 1] != '\'' 
			&& token->value[*i - 1] != '\"')
	{
		before_expand_def(token, *env, &i, copy);
		i++;
	}
	return (0);
}

int	begin_expand(t_token *token, t_env **env)
{
	t_token	*temp;
	int		*i;
	int		state;

	temp = token;
	i = 0;
	while (temp->value[*i])
	{	
		state = ft_get_state(temp->value[*i], state);
		if (state == DEFAULT)
			if (expand_def(temp, env, *i) == 1)
				return (1);
		else if (state == DOUBLE)
			if (expand_doub(temp, env, *i) == 1)
				return (1);
		else if (state == SINGLE)
			if (expand_sing(temp, env, *i) == 1)
				return (1);
		i++;
	}
	return (0);
}

int	expand(t_token **token, t_env **env)
{
	t_token	*temp;
	t_env	*tempEnv;

	temp = *token;
	tempEnv = *env;
	while (temp)
	{
		if (temp->type == ARG || temp->type == FD)
		{
			begin_expand(&temp, &tempEnv);
			if (begin_expand == 1)
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}