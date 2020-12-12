#include "asm.h"

t_label		*new_add_label(char *str)
{
	t_label *label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	label->next = NULL;
	label->name = ft_strdup(str);
    label->size = 0;
	return (label);
}

t_label     *ft_add_label(t_label **label, char *str)
{
    t_label	*next;
	t_label	*n_label;

	if (!(n_label = new_add_label(str)))
		return (NULL);
	next = *label;
	*label = n_label;
	n_label->next = next;
	return (n_label);
}

t_label     *add_label(char *str, t_label **label)
{
    if (!*label)
		return (*label = new_add_label(str));
	return ft_add_label(label, str);
}