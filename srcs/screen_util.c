/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sucho <sucho@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/15 10:16:58 by sucho             #+#    #+#             */
/*   Updated: 2020/09/24 12:06:24 by sucho            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			screen_exit(void)
{
	exit(0);
}

void		get_screen_res(int *mx_x, int *mx_y)
{
	CGRect	main_mointor;

	main_mointor = CGDisplayBounds(CGMainDisplayID());
	*mx_x = (int)CGRectGetWidth(main_mointor);
	*mx_y = (int)CGRectGetHeight(main_mointor);
}
