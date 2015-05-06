/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Event.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/04 13:45:09 by jaguillo          #+#    #+#             */
/*   Updated: 2015/05/06 12:12:03 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HPP
# define EVENT_HPP

class	Event
{
public:
	enum	Type
	{
		EVENT_UP,
		EVENT_RIGHT,
		EVENT_DOWN,
		EVENT_LEFT,
		EVENT_SPACE,
		EVENT_1,
		EVENT_2,
		EVENT_3,
		EVENT_4,
		EVENT_5,
		EVENT_6,
		EVENT_7,
		NOPE
	};

	Event(Type type);
	virtual ~Event(void);

	Type				getType(void) const;

	void				process(Game &game);

protected:

	typedef void		(Event::*event_t)(Game &);

	static event_t		_events[NOPE];

	Type				_type;

	void				_processUp(Game &game);
	void				_processRight(Game &game);
	void				_processDown(Game &game);
	void				_processLeft(Game &game);
	void				_processSpace(Game &game);
	void				_process1(Game &game);
	void				_process2(Game &game);
	void				_process3(Game &game);
	void				_process4(Game &game);
	void				_process5(Game &game);
	void				_process6(Game &game);
	void				_process7(Game &game);

private:
	Event(void);
	Event(Event const &src);
	Event				&operator=(Event const &rhs);
};

#endif
