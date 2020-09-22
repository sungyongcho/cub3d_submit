/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:16:58 by sucho             #+#    #+#             */
/*   Updated: 2020/09/23 06:14:33 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			screen_exit(void)
{
	exit(0);
}

void		setup_screen_res(int *mx_x, int *mx_y, int res_w, int res_h)
{
	CGRect	main_mointor;

	main_mointor = CGDisplayBounds(CGMainDisplayID());
	*mx_x = (int)CGRectGetWidth(main_mointor);
	*mx_y = (int)CGRectGetHeight(main_mointor);
	res_w = (*mx_x < res_w) ? res_w : *mx_x;
	res_h = (*mx_y < res_h) ? res_h : *mx_y;
}
