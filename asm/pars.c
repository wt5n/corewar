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
	return (srez);
}

int			pars_name(char *line, t_chempion *ch, t_new_st_label **label)
{
	char	*srez;
//	int		tecyhee=0;
	int		k=0;
	int probel = 0;
	int		len;

	/*tecyhee = kol_sim(line, '"');
	//printf("kol_sim %d\n", tecyhee);
	k = kol_sim(line[tecyhee], '"');
	if (tecyhee != -1 && tecyhee < k)
		k = tecyhee;
	srez = cut_one(line, line[k], 0);
	//printf("%s!\n", srez);*/
	//printf("%s!\n", line);
	if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 || \
				ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		
		
		if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
			{
				ch->flag = 1;
				//printf("line = %s\n", line);
				len = ft_strlen(NAME_CMD_STRING);
			}
		else
		{
			ch->flag = 2;
			len = ft_strlen(COMMENT_CMD_STRING);
		}
			probel = propysc_probel(&(line[len]));
				//printf("%d\n", probel);
				if (probel == -3 || line[probel + len] != '"')
					return -1;
		//	printf("name = !%s!\n", &(line[probel + len]));
			k = kol_sim(&(line[probel + len + 1]), '"');
		//	printf("%d\n", k);
			if (k == -1)
			return (-1);
			line[probel + len + 1 + k] = '\0';
			srez = ft_strdup(&line[probel + len + 1]);
			//srez3 = ft_strjoin(srez2, srez);
			//srez2 = ft_strdup(srez3);
			//while (get_next_line(fd, &line) > 0)
			//{

			//}
		//}
		
		
		
		//printf("srez = %s\n", srez);
	}
	else
		return (-1);
	zap_struct_ascii(ch, srez, label);
	return (1);
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
	//printf("%p    flag = %d\n", srez,ch->flag_label);
	zap_struct_ascii(ch, srez, label);
	free(srez);
	return (1);
}
