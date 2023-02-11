#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_test
{
	char *str;
	struct s_test	*next;
} t_test;


t_test *create(char *str) // creation du node, en remplissant sa data. dernier node pcq pointeur sur next = NULL 
{
	t_test *yo;

	yo = malloc(sizeof(t_test));
	yo->str = str;
	yo->next = NULL;
	return (yo);
}

void	insert(t_test **head, char *str) // inserer le node a la fin de la liste 
{
	t_test *new;
	t_test *temp;

	new = create(str);
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

void	printstr(t_test *head) // parcoure la liste et print la var que l'on veut | rentre dans un nouveau node en faisaint temp = temp->next
{
	t_test *temp = head;
	while (temp)
	{
		printf("%s ", temp->str);
		temp = temp->next;
	}
	printf("\n");
}

int	main()
{
	t_test *head = NULL;
	printf("ajout de node:");
	insert(&head, "hello");
	printstr(head);
	insert(&head, "yo");
	printf("ajout de node:");
	printstr(head);
	insert(&head,"wsh");
	printf("ajout de node:");
	printstr(head);
}
