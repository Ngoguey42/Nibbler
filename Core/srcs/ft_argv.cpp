/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juloo <juloo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 00:40:55 by juloo             #+#    #+#             */
/*   Updated: 2015/05/18 16:17:10 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_argv.h"
#include <stddef.h>

extern "C"
{

static char		*argvopt_long(t_args *args, char *tmp)
{
	if (tmp[2] == '\0')
	{
		args->c++;
		args->flags |= FTARGS_END;
		return (NULL);
	}
	args->i = 1;
	while (tmp[++(args->i)] != '=')
		if (tmp[args->i] == '\0')
		{
			args->c++;
			args->i = 1;
			return (tmp + 2);
		}
	args->flags |= FTARGS_LONG;
	tmp[args->i] = '\0';
	return (tmp + 2);
}

char			*ft_argvopt(t_args *args)
{
	char			*tmp;

	if (args->flags & FTARGS_LONG)
	{
		args->flags &= ~FTARGS_LONG;
		args->c++;
		args->i = 1;
	}
	while (args->c < args->argc && !(args->flags & FTARGS_END))
	{
		tmp = args->argv[args->c];
		if (!(tmp[0] == '-' && tmp[1] != '\0'))
			break ;
		if (tmp[1] == '-')
			return (argvopt_long(args, tmp));
		if (tmp[args->i] != '\0')
		{
			args->opt[0] = tmp[args->i++];
			return (args->opt);
		}
		args->i = 1;
		args->c++;
	}
	args->flags |= FTARGS_END;
	return (NULL);
}

char			*ft_argvarg(t_args *args)
{
	char			*tmp;

	if (args->flags & FTARGS_LONG)
	{
		args->flags &= ~FTARGS_LONG;
		tmp = args->argv[args->c] + args->i + 1;
		args->c++;
		args->i = 1;
		return (tmp);
	}
	while (args->c < args->argc)
	{
		tmp = args->argv[args->c++];
		if (!(tmp[0] == '-' && tmp[1] != '\0'))
			return (tmp);
		tmp += args->i;
		args->i = 1;
		if (*tmp != '\0')
			return (tmp);
	}
	return (NULL);
}

};
