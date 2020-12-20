#include "asm.h"

t_label		*new_add_label(char *str)
{
	t_label *label;

	if (!(label = (t_label *)malloc(sizeof(t_label))))
		return (NULL);
	label->next = NULL;
	label->name = ft_strdup(str);
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

t_new_st_label		*new_st_add_label(char *str)
{
	t_new_st_label	*label;

	if (!(label = (t_new_st_label *)malloc(sizeof(t_new_st_label))))
		return (NULL);
	label->lab = new_add_label(str);
	label->next = NULL;
	label->lab->op = NULL;
	return (label);
}

t_new_st_label		*ft_st_add_label(t_new_st_label **label, char *str)
{
    t_new_st_label	*next;
	t_new_st_label	*n_label;

	if (!(n_label = new_st_add_label(str)))
		return (NULL);
	next = *label;
	*label = n_label;
	n_label->next = next;
	return (n_label);
}

t_new_st_label     *add_st_label(char *str, t_new_st_label **label)
{
    if (!*label)
		return (*label = new_st_add_label(str));
	return ft_st_add_label(label, str);
}

t_op_strukt		*new_op_struct()
{
	t_op_strukt	*op;

	if (!(op = (t_op_strukt *)malloc(sizeof(t_op_strukt))))
		return (NULL);
	op->name = 0;
	op->size = 0;
	op->stroca = NULL;
	op->next = NULL;
	return (op);
}

t_op_strukt     *ft_add_op_struct(t_op_strukt **op)
{
    t_op_strukt	*next;
	t_op_strukt	*n_op;

	if (!(n_op = new_op_struct()))
		return (NULL);
	next = *op;
	*op = n_op;
	n_op->next = next;
	return (n_op);
}

t_op_strukt    *add_op_struct(t_op_strukt **label)
{
    if (!*label)
		return (*label = new_op_struct());
	return ft_add_op_struct(label);
}