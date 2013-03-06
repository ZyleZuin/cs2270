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

/**
 * Initialize an empty priority queue.
 *
 * This is needed for unit testing. I'll do something like this:
 *
 *   pq* queue = init_priority_queue();
 *   string text = "Speaker of the House";
 *   insert(queue,  text, 7.9);
 *   text = "President";
 *   insert(queue, text, 10.0);
 *   text = "Congressional Staffer";
 *   insert(queue, text, 2.0);
 *   cout << remove(queue) << endl; // President
 *   cout << remove(queue) << endl; // Speaker of the House
 *   cout << remove(queue) << endl; // Congressional Staffer
 *
 **/
pq* init_priority_queue() {
	pq* q = new pq;
	q->next = NULL;
	q->previous = NULL;
	q->priority = 0.0;
	q->text = "";
	q->empty = true;
	return q;
}

/**
 * Insert the given text information into the queue with the specified
 * priority.
 *
 * Larger priority values have precedence. So if I add "foo" at
 * priority 5.0 and "bar" at priority 5.1, "bar" will be removed
 * before "foo".
 *
 * Priority values may be negative, zero, or positive.
 **/
void insert(pq* &queue, string &text, float priority) {
	if (queue->empty == true) {
		queue->text = text;
		queue->priority = priority;
		queue->empty = false;
	} else {
		if (priority > queue->priority) {
			if (queue->previous == NULL) {
				pq* q = new pq;
				q->next = queue->next;
				q->previous = queue;
				q->priority = queue->priority;
				q->text = queue->text;
				queue->priority = priority;
				queue->text = text;
				queue->next = q;
			} else {
				pq* q = new pq;
				q->priority=priority;
				q->text=text;
				q->next = queue;
				q->previous = queue->previous;
				queue->previous->next = q;
				queue->previous = q;
			}
		} else {
			if (queue->next != NULL) {
				insert(queue->next, text, priority);
			} else {
				pq* q = new pq;
				q->priority=priority;
				q->text=text;
				q->next =NULL;
				q->previous = queue;
				queue->next=q;
			}
		}
	}
}

/**
 * Remove the highest priority element from the queue and return it.
 **/
string remove(pq* &queue) {
	if (queue == NULL) {
		return "Empty Queue";
	} else {
		string removed_value = queue->text;
		queue = queue->next;
		return removed_value;
	}
}

/**
 * Return the highest priority element in the queue but do not alter
 * the queue's membership.
 **/
string peek(pq* &queue) {
	return queue->text;
}
