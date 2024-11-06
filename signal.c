/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lufiguei <lufiguei@student.42porto.co      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:09:44 by lufiguei          #+#    #+#             */
/*   Updated: 2024/11/06 17:09:53 by lufiguei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    sighandler(int signal)
{
    if (signal == SIGINT) // ctrl + c
    {
        // gives back a new prompt on a new line
    }
    else if (signal == SIGQUIT)
    {
        // does nothing
    }
}

// call on 'signalizer':
// signal(SIGINT, sighandler);
// signal(SIGQUIT, sighandler);
