/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minjacho <minjacho@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/23 13:46:46 by minjacho          #+#    #+#             */
/*   Updated: 2023/12/26 19:34:03 by minjacho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_valid_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			if (!(str[i] == '+' || str[i] == '-' || str[i] == ' '))
				return (0);
		}
		i++;
	}
	return (1);
}

char	*get_next_line_wo_nl(int fd)
{
	char	*line;
	char	*result;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	result = ft_strtrim(line, "\n");
	if (!result)
		exit_malloc_error();
	free(line);
	if (!is_valid_line(result))
		exit_not_valid_input();
	return (result);
}

int	get_one_line_input(int fd, int **nums)
{
	char	*line;
	char	**str_nums;
	int		size;
	int		idx;

	line = get_next_line_wo_nl(fd);
	if (!line)
		return (-1);
	str_nums = ft_split(line, ' ');
	if (!str_nums)
		exit_malloc_error();
	size = 0;
	while (str_nums[size])
		size++;
	*nums = (int *)malloc(sizeof(int) * size);
	idx = 0;
	while (idx < size)
	{
		(*nums)[idx] = ft_atoi(str_nums[idx]);
		idx++;
	}
	free(line);
	free_double_ptr(str_nums);
	return (size);
}

t_input	*make_new_node(int fd)
{
	int		*nums;
	int		size;
	t_input	*new_node;

	size = get_one_line_input(fd, &nums);
	if (size < 0)
		return (NULL);
	new_node = (t_input *)malloc(sizeof(t_input));
	if (!new_node)
		exit_malloc_error();
	new_node->nums = nums;
	new_node->size = size;
	new_node->next = NULL;
	return (new_node);
}

t_input	*read_file(int fd)
{
	t_input	*tmp;
	t_input	*start;

	start = make_new_node(fd);
	tmp = start;
	while (tmp)
	{
		tmp->next = make_new_node(fd);
		tmp = tmp->next;
	}
	return (start);
}