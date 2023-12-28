/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jberay <jberay@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 09:30:36 by jberay            #+#    #+#             */
/*   Updated: 2023/12/28 08:45:29 by jberay           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	sort_three(t_stack **head)
{
	t_stack	*hold;

	hold = find_max(*head);
	if (*head == hold)
		ra(head);
	else if ((*head)->next == hold)
		rra(head);
	if ((*head)->final_pos > (*head)->next->final_pos)
		sa(head);
}

static void	prep_for_push(t_stack **head, t_stack *top, char name)
{
	while (*head != top)
	{
		if (name == 'a')
		{
			if (top->above)
				ra(head);
			else
				rra(head);
		}
		else if (name == 'b')
		{
			if (top->above)
				rb(head);
			else
				rrb(head);
		}
	}
}

static void	rotate(t_stack **a_head, t_stack **b_head, t_stack *cheapest)
{
	while (*b_head != cheapest->target && *a_head != cheapest)
	{
		rr(a_head, b_head);
	}
	current_index(*a_head);
	current_index(*b_head);
}

static void	rev_rotate(t_stack **a_head, t_stack **b_head, t_stack *cheapest)
{
	while (*b_head != cheapest->target && *a_head != cheapest)
	{
		rrr(a_head, b_head);
	}
	current_index(*a_head);
	current_index(*b_head);
}

static void	push_atob(t_stack **a_head, t_stack **b_head)
{
	t_stack	*cheapest;

	cheapest = get_cheapest(*a_head);
	if (cheapest->above && cheapest->target->above)
		rotate(a_head, b_head, cheapest);
	else if ((!cheapest->above) && !(cheapest->target->above))
		rev_rotate(a_head, b_head, cheapest);
	prep_for_push(a_head, cheapest, 'a');
	prep_for_push(b_head, cheapest->target, 'b');
	pb(a_head, b_head);
}

static void	push_btoa(t_stack **a_head, t_stack **b_head)
{
	prep_for_push(a_head, (*b_head)->target, 'a');
	pa(a_head, b_head);
}

static void	min_top(t_stack **a_head)
{
	while ((*a_head)->final_pos != find_min(*a_head)->final_pos)
	{
		if (find_min(*a_head)->above)
			ra(a_head);
		else
			rra(a_head);
	}
}

void	sort_big(t_stack **a_head, t_stack **b_head)
{
	if (ps_lstsize(*a_head) > 3 && !sorted(*a_head))
		pb(a_head, b_head);
	if (ps_lstsize(*a_head) > 3 && !sorted(*a_head))
		pb(a_head, b_head);
	while (ps_lstsize(*a_head) > 3 && !sorted(*a_head))
	{
		init_a(*a_head, *b_head);
		push_atob(a_head, b_head);
	}
	sort_three(a_head);
	while (*b_head)
	{
		init_b(*a_head, *b_head);
		push_btoa(a_head, b_head);
	}
	current_index(*a_head);
	min_top(a_head);
}

int	sorted(t_stack *head)
{
	t_stack	*ptr;

	ptr = head;
	while (ptr->next)
	{
		if (ptr->final_pos > ptr->next->final_pos)
			return (0);
		ptr = ptr->next;
	}
	return (1);
}

