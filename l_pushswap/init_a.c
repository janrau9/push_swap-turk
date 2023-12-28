/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 07:31:28 by jberay            #+#    #+#             */
/*   Updated: 2023/12/28 08:23:53 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	current_index(t_stack *head)
{
	int	i;
	int	median;

	i = 0;
	if (!head)
		return ;
	median = ps_lstsize(head) / 2;
	while (head)
	{
		head->index = i;
		if (i <= median)
			head->above = true;
		else
			head->above = false;
		head = head->next;
		i++;
	}
}

static void	find_atob(t_stack *a_head, t_stack *b_head)
{
	t_stack	*hold;
	t_stack	*target;
	long	match_index;

	while (a_head)
	{
		match_index = LONG_MIN;
		hold = b_head;
		while (hold)
		{
			if (hold->final_pos < a_head->final_pos
				&& hold->final_pos > match_index)
			{
				match_index = hold->final_pos;
				target = hold;
			}
			hold = hold->next;
		}
		if (match_index == LONG_MIN)
			a_head->target = find_max(b_head);
		else
			a_head->target = target;
		a_head = a_head->next;
	}
}

static void	cost_a(t_stack *a_head, t_stack *b_head)
{
	int	size_a;
	int	size_b;

	size_a = ps_lstsize(a_head);
	size_b = ps_lstsize(b_head);

	while (a_head)
	{
		a_head->push_cost = a_head->index;
		if (!(a_head->above))
			a_head->push_cost = size_a - (a_head->index);
		if (a_head->target->above)
			a_head->push_cost = a_head->push_cost + a_head->target->index;
		else
			a_head->push_cost += size_b - a_head->target->index;
		a_head = a_head->next;
	}
}

static void	cheapest(t_stack *head)
{
	long	cheapest;
	t_stack	*hold;

	if (!head)
		return ;
	cheapest = LONG_MAX;
	while (head)
	{
		if (head->push_cost < cheapest)
		{
			cheapest = head->push_cost;
			hold = head;
		}
		head = head->next;
	}
	hold->cheapest = true;
}

void	init_a(t_stack *a_head, t_stack *b_head)
{
	current_index(a_head);
	current_index(b_head);
	find_atob(a_head, b_head);
	cost_a(a_head, b_head);
	cheapest(a_head);
}