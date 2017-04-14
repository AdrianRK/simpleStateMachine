/*
 * machine.hpp
 *
 *  Created on: Apr 4, 2017
 *      Author: devteam
 */

#ifndef MACHINE_HPP_
#define MACHINE_HPP_

#include <map>


typedef unsigned int state_;
typedef enum {E1,E2,E3,E4} event_;

class action_
{
public:
	virtual ~action_()
	{}
	virtual void operator()() = 0;
};

template <typename _event_ = event_, typename _state_ = state_, typename _action_ = action_>
class machine
{
public:
	typedef _event_ event;
	typedef _state_ state;
	typedef _action_ action;


	machine():currState(0),initialised(false){}
	virtual void addNewTransition(const state &S1, const event&E, const state&S2);
	virtual void processEvent(const event&);
	virtual void addNewState(const state &S, action*A);
	virtual ~machine();
private:

	std::map<state, action*> Statelist;
	std::map<state, std::map<event,state>> transitions;
	state currState;
	bool initialised;
};

template <typename _event_, typename _state_ , typename _action_>
void machine<_event_, _state_, _action_>::addNewTransition(const state &S1, const event&E, const state&S2)
{
	if(Statelist.end() == Statelist.find(S1) || Statelist.end() == Statelist.find(S2))
	{
		return;
	}
	PRINT_INFO("Insert transition from ",S1, " to ", S2, " with the event ", E);

	if(transitions.end() == transitions.find(S1))
	{
		std::map<event, state> connection;
		connection.insert(std::pair<event,state>(E, S2));
		std::pair<state, std::map<event,state>> transition(S1, connection);
		transitions.insert(transition);
	}
	else
	{
		if(transitions[S1].end() == transitions[S1].find(E))
		{
			transitions[S1].insert(std::pair<event,state>(E,S2));
		}
		else
		{
			transitions[S1][E] = S2;
		}
	}
}

template <typename _event_, typename _state_, typename _action_>
void machine<_event_, _state_, _action_>::addNewState(const state &S, action*A)
{
	PRINT_INFO("Insert State ",S ," and action ", A);
	if(Statelist.end() == Statelist.find(S))
	{
		Statelist.insert(std::pair<state, action*> (S,A));
	}
	else
	{
		Statelist[S] = A;
	}
	if(false == initialised)
	{
		initialised = true;
		currState = S;
	}
}

template <typename _event_, typename _state_, typename _action_>
void machine<_event_, _state_, _action_>::processEvent(const event &E)
{
	if(false == initialised)
	{
		return;
	}
	if(transitions[currState].end() != transitions[currState].find(E))
	{
		PRINT_INFO("Transition from state ", currState, " to state ", transitions[currState][E], " for event ", E);
		currState = transitions[currState][E];
		if(nullptr != Statelist[currState])
		{
			(*Statelist[currState])();
		}
	}
}

template <typename _event_, typename _state_, typename _action_>
machine<_event_, _state_, _action_>::~machine()
{
	for( auto it : Statelist)
	{
		delete it.second;
		it.second = nullptr;
	}
}

#endif /* MACHINE_HPP_ */
