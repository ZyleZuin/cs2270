/*

 fsm.cpp - Finite State Machine

 Read the header file 'fsm.hpp' for all documentation on individual
 functions. I suggest you start by getting the unit test cases to
 pass in order. E.g. start with the Defaults one, then do Add States,
 and so on.

 Your Name:

 Your Collaborators:

 */

#include "fsm.hpp"

using namespace std;

FSM::FSM() {
	state = -1;
	default_state = -1;
}
int FSM::addState(string label, bool is_accept_state) {
	State* st = new State;
	st->label = label;
	st->accept = is_accept_state;
	int id = states.size();
	states.push_back(st);
	if (states.size() == 1) {
		state = id;
		default_state = id;
	}
	return id;
}
int FSM::addState(string label) {
	State* st = new State;
	st->label = label;
	st->accept = false;
	int id = states.size();
	states.push_back(st);
	if (states.size() == 1) {
		state = id;
		default_state = id;
	}
	return id;
}

int FSM::addTransition(int stateA, int stateB, int signal, string transLabel) {
	if(stateA<0) {
		return -1;
	}

	int state_size = states.size();
	int trans_size = getState(stateA)->trans.size();
	bool aExists = false;
	bool bExists = false;
	bool dup = false;
	//Check if states exist
	for (int i = 0; i < state_size; i++) {
		if (stateA == i) {
			aExists = true;
		}
		if (stateB == i) {
			bExists = true;
		}
	}
	//Check for duplicate
	for (int i = 0; i < trans_size; i++) {
		Transition* tr = getTransition(getState(stateA)->trans[i]);
		if (stateB == tr->next_state) {
			dup = true;
		}
	}

	if (aExists && bExists && !dup) {

		State* st = getState(stateA);
		Transition* trans = new Transition;
		trans->next_state = stateB;
		trans->signal = signal;
		trans->label = transLabel;
		int id = transitions.size();
		transitions.push_back(trans);
		st->trans.push_back(id);
		return id;
	} else
		return -1;
}

int FSM::countStates() {
	return states.size();
}

int FSM::countTransitions() {
	return transitions.size();
}

int FSM::getCurrentState() {
	return state;
}
bool FSM::isAcceptState() {
	if (state == -1) {
		return false;
	} else {
		return getState(state)->accept;
	}
}
State* FSM::getState(int id) {
	if (states.size() == 0) {
		return NULL;
	} else {
		return states[id];
	}
}

Transition* FSM::getTransition(int id) {
	int size = transitions.size();
	if (size == 0) {
		return NULL;
	} else if (id > size) {
		return NULL;
	} else {
		return transitions[id];
	}
}

int FSM::getDefaultState() {
	return default_state;
}

void FSM::setState(int id) {
	state = id;
}
bool FSM::handleSignal(int signal) {
	if (state == -1) {
		return false;
	}
	State* current_state = getState(state);
	int num_trans = current_state->trans.size();
	for (int i = 0; i < num_trans; i++) {
		Transition* current_trans = getTransition(current_state->trans[i]);
		if (signal == current_trans->signal) {
			setState(current_trans->next_state);
			return true;
		}
	}

	for (int i = 0; i < num_trans; i++) {
		Transition* current_trans = getTransition(current_state->trans[i]);
		if (current_trans->signal == -1) {
			setState(current_trans->next_state);
		}
	}
	return false;
}
ostream &operator <<(ostream& out, State* st) {
	if (st == NULL) {
		out << "State: NULL";
	} else {
		out << "State: " << st->label;
		if (st->accept) {
			out << " +";
		}
	}
	return out;
}
