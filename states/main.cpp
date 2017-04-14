/*
 * main.cpp
 *
 *  Created on: Apr 4, 2017
 *      Author: devteam
 */
#include "logger.hpp"
#include "machine.hpp"

class actionSt/* : public action_*/
{
public:
	actionSt(const std::string &S):message(S){}
	~actionSt() {PRINT_INFO("Cleanup")}
	void operator()()
	{
		PRINT_INFO(message);
	}
private:
		std::string message;
};

enum class Events {e1,e2,e3,e4,e5,e6};

std::ostream& operator <<(std::ostream& cout, Events e)
{
	switch(e)
	{
	case Events::e1: cout <<"Event 1";break;
	case Events::e2: cout <<"Event 2";break;
	case Events::e3: cout <<"Event 3";break;
	case Events::e4: cout <<"Event 4";break;
	case Events::e5: cout <<"Event 5";break;
	case Events::e6: cout <<"Event 6";break;
	default: cout <<""; break;
	}
	return cout;
}

int main(int argc, char **argv)
{
	PRINT_INFO("Software start!");
	//machine<event_, state_> myMKachine;
	machine<Events, state_, actionSt> myMKachine;

	myMKachine.addNewState(1,new actionSt("Action for state 1"));
	myMKachine.addNewState(2,new actionSt("Action for state 2"));
	myMKachine.addNewState(3,new actionSt("Action for state 3"));
	myMKachine.addNewState(4,new actionSt("Action for state 4"));
	myMKachine.addNewState(5,new actionSt("Action for state 5"));
	myMKachine.addNewState(6,new actionSt("Action for state 6"));

	myMKachine.addNewTransition(1, Events::e1, 2);
	myMKachine.addNewTransition(1, Events::e2, 3);
	myMKachine.addNewTransition(2, Events::e3, 4);
	myMKachine.addNewTransition(2, Events::e4, 1);
	myMKachine.addNewTransition(3, Events::e3, 1);
	myMKachine.addNewTransition(3, Events::e4, 4);
	myMKachine.addNewTransition(4, Events::e1, 5);
	myMKachine.addNewTransition(5, Events::e1, 6);
	myMKachine.addNewTransition(5, Events::e4, 2);


	myMKachine.processEvent(Events::e1);
	myMKachine.processEvent(Events::e3);
	myMKachine.processEvent(Events::e1);
	myMKachine.processEvent(Events::e1);

	PRINT_INFO("Software end!");
}
