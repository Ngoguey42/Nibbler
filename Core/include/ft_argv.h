/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/18 14:25:13 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/18 17:13:28 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ARGV_H
# define FT_ARGV_H

extern "C"
{

# define FTARGS_END			(1 << 2) // Options ended or "--" occur
# define FTARGS_LONG		(1 << 3) // In a long option

typedef struct	s_args
{
	char			**argv;
	int				argc;
	int				flags;
	int				c;
	int				i;
	char			opt[2];
}				t_args;

/*
** ARGS
** ---
** Init a 't_args' struct
** ---
*/
#define ARGS(c,v)		((t_args){(v), (c), 0, 1, 1, {'\0', '\0'}})

/*
** ARGS_DATA
** ---
** Detect if the current option is a long option and have data
** Example: "--opt=data"
** -
** A call to 'ft_argvarg' will return 'data'
** ---
** Return 'true' if the current option is long and have data
** 'false' otherwise
** ---
*/
#define ARGS_DATA(a)	(((a).flags) & FTARGS_LONG)

/*
** ft_argvarg
** ---
** Iter over arguments
** -
** Used with ft_argvopt can return the value of an option
**  ex: "-clol": ft_argvopt return "c", ft_argvarg return "lol"
**  ex: "-c" "lol": ft_argvopt return "c", ft_argvarg return "lol"
**  ex: "--lol=c": ft_argvopt return "lol", ft_argvarg return "c"
** ---
** Return an argument
** ---
*/
char			*ft_argvarg(t_args *args);

/*
** ft_argvopt
** ---
** Iter over options
** -
** Example:
**  For arguments "-a" "-bcd" "--abc" "--def=x"
**  Options are: "a", "b", "c", "d", "abc", "def"
** -
** "--", "-" or any argument that do not start with '-' stop iteration
** ---
** Warning: Can write into argv for long options
** ---
** Return an option or NULL if options ended
** ---
*/
char			*ft_argvopt(t_args *args);

};

#endif
