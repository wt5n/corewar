/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 22:57:02 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/16 19:46:10 by wtsn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void				zap_struct_ascii(t_chempion *ch, char *str, \
		t_new_st_label **label)
{
	t_new_st_label *label2;
	//printf("len = %zu\n", ft_strlen(str));
	if (ch->flag == 1 && ft_strlen(str) <= PROG_NAME_LENGTH)
		ch->name = ft_strdup(str);
	else if (ch->flag == 2 && ft_strlen(str) <= COMMENT_LENGTH)
		ch->comment = ft_strdup(str);
	else if (ch->flag == 3 && proverca_label(str) > 0)
	{
		
		if (ch->flag_label == 1)
			{label2 = label_last(label);
				add_label(str, &(label2->lab));
			}
		else
		{
			ch->flag_label = 1;
			add_st_label(str, label);
		}
	}
}

int					read_line(int fd, t_chempion *ch, t_new_st_label **label, \
		t_op_strukt **op)
{
	char			*line;
	int				k;
	//int				k2;
	//t_comment		*co;

	k = 0;
	/*ch->co = (t_comment*)malloc(sizeof(t_comment));
	co = ch->co;
	co->com = NULL;
	co->next = NULL;*/
	while (get_next_line(fd, &line) > 0)
	{	
		if (ch->i != 0)
		{
			int i = 0;
			while (line[i] != '\0' && line[i] != '"')
			{
				ch->comment[ch->i] = line[i];
				i++;
				ch->i++;
			}
			if (line[i] == '"')
			{
				while (ch->i < COMMENT_LENGTH)
				{
					ch->comment[ch->i] = 0;
					ch->i++;
				}
				ch->i = 0;
			}
			else
			{
				ch->comment[ch->i] = '\n';
				ch->i++;
			}
			
			/*printf("####!%s!\n", line);
			k2 = kol_sim(line, '"');
			if (k2 != -1)
			{
				line[k2] = '\0';
				co->com = ft_strdup(line);
				printf("!%s!\n", co->com);
				ch->len_com += ((int)ft_strlen(co->com));
				printf("len = %d\n", ((int)ft_strlen(co->com)));
				ch->i = 0;
			}
			else
			{
				co->com = ft_strdup(line);
				ch->len_com += ((int)ft_strlen(co->com));
				co->next = (t_comment*)malloc(sizeof(t_comment));
				co->next->com = NULL;
				co->next->next = NULL;
				co = co->next;
			}
			free(line);*/
		}
		else
		if (ch->n != 0)
		{
			int n = 0;
			while (line[n] != '\0' && line[n] != '"')
			{
				ch->name[ch->n] = line[n];
				n++;
				ch->n++;
			}
			if (line[n] == '"')
			{
				while (ch->n < PROG_NAME_LENGTH)
				{
					ch->name[ch->n] = 0;
					ch->n++;
				}
				ch->n = 0;
			}
			else
			{
				ch->name[ch->n] = '\n';
				ch->n++;
			}
		}
			else
		{
			k++;
		int probel = propysc_probel(line);
		if (probel != -3)
		{
			if (pars_one(line, ch, label, op) < 0)
			{
			printf("number = %d   line = %s\n", k, line); //zamena
			free(line);
			return (-1);
			}
		}
		free(line);
		}
	}
	if (ch->i == 1)
		return (-1);
	return (1);
}

int					file_argv(char *str)
{
	if (str[ft_strlen(str) - 1] == 's' && str[ft_strlen(str) - 2] == '.')
		return (1);
	return (-1);
}

void				init_asm(t_chempion *ch, t_new_st_label **label, \
		t_op_strukt **op)
{
	ch->name = (char*)malloc(sizeof(char) * PROG_NAME_LENGTH + 1);
	ch->comment = (char*)malloc(sizeof(char) * COMMENT_LENGTH + 1);
	ch->comment[COMMENT_LENGTH] = '\0';
	ch->name[PROG_NAME_LENGTH] = '\0';
	ch->code = NULL;
	ch->flag_label = 0;
	ch->smehenee = 0;
	ch->size = 0;
	ch->i = 0;	
	ch->n = 0;
	ch->len_com = 0;
	ch->co = NULL;
	//ch->co->com = NULL;
	//ch->co->next = NULL;
	(*op) = NULL;
	(*label) = NULL;
	zap_registr(ch);
}

int					main(int argc, char *argv[])
{
	int				fd;
	t_chempion		ch;
	t_new_st_label	*label;
	t_op_strukt		*op;

	if (argc == 2)
	{
		if (file_argv(argv[1]) < 0 || (fd = open(argv[1], O_RDONLY)) < 0)
			return (-1);
		init_asm(&ch, &label, &op);
		ch.fd = fd;
		if (read_line(fd, &ch, &label, &op) < 0)
			{
				write(2, "Error_read\n", 11);
				return (-1);
			}
				
	}
	else
		return (-1);
	//print_struct(label);
	trace_byte_code(&ch, label, op);
	close(fd);
	if (write_code(argv[1], ch) < 0)
		return (-1);
	/*printf("%s\n", ch.name);
	printf("%s\n", ch.comment);
	
	print_op(op);*/
	return (0);
}
