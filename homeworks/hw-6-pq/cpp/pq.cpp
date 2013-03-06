//
// pq.cpp
//
// Decide how you want to implement this: linked list? heap? array?
// magic pixie dust? The choice is yours.
//
// NOTE: You will need to edit pq_struct.h as appropriate, depending
// on your implementation strategy. You will turn in this file (your
// implementation of everything) and pq_struct.h (your definition of
// the pq structure and any helper functions you might create).

// Your Name:

#include <string>
#include "pq.h"

void insert(pq* &queue, string &text, float priority) {
	if (queue == NULL) {
		pq* new_pq = new pq;
		new_pq->priority = priority;
		new_pq->text = text;
		new_pq->next = NULL;
		new_pq->previous = NULL;
	} else if (priority > queue->priority) {
		pq* new_pq = new pq;
		new_pq->priority = priority;
		new_pq->text = text;
		new_pq->next = queue;
		new_pq->previous = queue->previous;
		queue->previous = new_pq;
		queue->previous->next = new_pq;
	} else {
		if (queue->next != NULL) {
			insert(queue->next, text, priority);
		} else {
			pq* new_pq = new pq;
			new_pq->priority = priority;
			new_pq->text = text;
			new_pq->next = NULL;
			new_pq->previous = queue;
		}
	}
}

string remove(pq* &queue) {
	if (queue == NULL) {
		return "Empty Queue";
	} else {
		string removed_value = queue->text;
		queue = queue->next;
		return removed_value;
	}
}

string peek(pq* &queue) {
	return queue->text;
}
