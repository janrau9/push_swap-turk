/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 08:14:11 by jberay            #+#    #+#             */
/*   Updated: 2023/12/28 08:24:54 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	find_btoa(t_stack *a_head, t_stack *b_head)
{
	t_stack	*hold;
	t_stack	*target;
	long	match_index;

	while (b_head)
	{
		match_index = LONG_MAX;
		hold = a_head;
		while (hold)
		{
			if (hold->final_pos > b_head->final_pos
				&& hold->final_pos < match_index)
			{
				match_index = hold->final_pos;
				target = hold;
			}
			hold = hold->next;
		}
		if (match_index == LONG_MAX)
			b_head->target = find_min(a_head);
		else
			b_head->target = target;
		b_head = b_head->next;
	}
}



void	init_b(t_stack *a_head, t_stack *b_head)
{
	current_index(a_head);
	current_index(b_head);
	find_btoa(a_head, b_head);
}