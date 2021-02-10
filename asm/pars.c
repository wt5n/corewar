/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heantoni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 20:33:46 by heantoni          #+#    #+#             */
/*   Updated: 2021/01/20 21:01:15 by heantoni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

char		*cut_one(char *str, char c, int n)
{
	char	*srez;
	char	*srez2;
	int		n_line;

	n_line = kol_sim(&(str[n]), c);
	srez2 = ft_strdup(str);
	if (n_line != -1 && n_line != (int)ft_strlen(str))
		srez2[n_line] = '\0';
	srez = ft_strdup(srez2);
	free(srez2);
	return (srez);
}

int			pars_name(char *line, t_chempion *ch)
{
	int		k=0;
	int probel = 0;
	int		len;

	if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 || \
				ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
			{
				ch->flag = 1;
				len = ft_strlen(NAME_CMD_STRING);
			}
		else
		{
			ch->flag = 2;
			len = ft_strlen(COMMENT_CMD_STRING);
		}
			probel = propysc_probel(&(line[len]));
			if (probel == -3 || line[probel + len] != '"')
					return -1;
			k = kol_sim(&(line[probel + len + 1]), '"');
			if (ch->flag == 2 && k == -1)
			{
				int i=probel + len + 1;
				while (line[i] != '\0' && line[i] != '"')
					{
						ch->comment[ch->i] = line[i];
						ch->i += 1;
						i++;
					}
					ch->comment[ch->i] = '\n';
					ch->i++;
					return (1);
			}
			else if (ch->flag == 2)
			{
				int i=probel + len + 1;
				while (line[i] != '\0' && line[i] != '"')
					{
						ch->comment[ch->i] = line[i];
						ch->i++;
						i++;
					}
				while (ch->i < COMMENT_LENGTH)
					{
						ch->comment[ch->i] = 0;
						ch->i++;
					}
					ch->i = 0;
				return 1;
			}
			if (ch->flag == 1 && k == -1)
			{
				int n=probel + len + 1;
				while (line[n] != '\0' && line[n] != '"')
					{
						ch->name[ch->n] = line[n];
						ch->n += 1;
						n++;
					}
					ch->name[ch->n] = '\n';
					ch->n++;
					return (1);
			}
			else if (ch->flag == 1)
			{
				int n=probel + len + 1;
				while (line[n] != '\0' && line[n] != '"')
					{
						ch->name[ch->n] = line[n];
						ch->n++;
						n++;
					}
				while (ch->n < PROG_NAME_LENGTH)
					{
						ch->name[ch->n] = 0;
						ch->n++;
					}
					ch->n = 0;
				return 1;
			}
	}
		return (-1);
}

int			proverca_label(char *str)
{
	int		i;
	int		k;
	char	*label_char;

	i = 0;
	label_char = LABEL_CHARS;
	while (str[i] != '\0')
	{
		k = 0;
		while (label_char[k] != '\0' && label_char[k] != str[i])
			k++;
		if (label_char[k] == '\0')
			return (-1);
		i++;
	}
	return (1);
}

int			par_l(char *line, t_chempion *ch, t_new_st_label **label)
{
	char	*srez;

	srez = ft_strdup(line);
	ch->flag = 3;
	zap_struct_ascii(ch, srez, label);
	free(srez);
	return (1);
}
