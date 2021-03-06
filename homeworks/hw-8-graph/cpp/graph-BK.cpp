/*
 Graph.cpp

 This is your implementation file for the depth-first and
 breadth-first search assignment. All the documentation and
 instructions are in the header file.

 Your Name:

 Your Collaborators:

 */
#include <iostream>
#include <string>
#include <set>
#include "graph.hpp"

using namespace std;

Graph::Graph() {
	// graphs are undirected by default
	directed = false;
}

Graph::~Graph() {

}

vector<Node*> Graph::getNodes() {
	return nodes;
}

vector<Edge*> Graph::getEdges() {
	return edges;
}

int Graph::getClock() {
	return clock;
}

void Graph::addNode(Node& n) {
	nodes.push_back(&n);
}

void Graph::addEdge(Edge& e) {
	edges.push_back(&e);
}

void Graph::removeNode(Node& n) {
	for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
		if (&n == *it) {
			nodes.erase(it);
			break;
		}
	}
}

void Graph::removeEdge(Edge& e) {
	for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
		if (&e == *it) {
			edges.erase(it);
			break;
		}
	}
}

void Graph::setDirected(bool val) {
	directed = val;
}

bool Graph::isDirected() {
	return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node& n) {
	set<Edge*> ret;
	for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
		Edge* edge = *it;
		if (edge->getStart() == &n) {
			ret.insert(edge);
		}
		if (!directed && edge->getEnd() == &n) {
			ret.insert(edge);
		}
	}
	return ret;
}

void Graph::clear() {
	clock = 0;
	// nodes is vector<Node*>
	//  for (size_t i = 0; i < nodes.size(); i++) {
	//    Node* n = nodes[i];
	//  }
	vector<Node*>::iterator it = nodes.begin();
	for (; it != nodes.end(); it++) {
		Node* n = *it;
		n->clear();
	}
	vector<Edge*>::iterator eit = edges.begin();
	for (; eit != edges.end(); eit++) {
		Edge* e = *eit;
		e->setType(UNDISCOVERED_EDGE);
	}

}

void Graph::tick(string message) {
	// optional debugging function
}

void Graph::dfs(Node& start) {
	int color;
	int disco_time;
	int finish_time;
	int bfs_rank;
	vector<Edge*> my_edges;

	clock++;
	start.getDiscoveryInformation(color, disco_time, finish_time, bfs_rank);

	if (color == WHITE) {
		start.setColor(GRAY, clock);
		for (size_t i = 0; i < edges.size(); i++) {
			Edge* edge = edges[i];
			if (edge->getStart() == &start) {
				edge->getEnd()->setPredecessor(start);
				my_edges.push_back(edges[i]);
			}
		}
	}
	for (size_t i = 0; my_edges.size(); i++) {
		Edge* edge = my_edges.back();
		my_edges.pop_back();
		edge->getEnd()->getDiscoveryInformation(color, disco_time, finish_time,
				bfs_rank);
		if (color == GRAY) {
			edge->setType(BACK_EDGE);
		} else if (color == BLACK) {
			if (edge->getStart()->isAncestor(*edge->getEnd()) == true) {
				edge->setType(FORWARD_EDGE);
			} else {
				edge->setType(CROSS_EDGE);
			}
		} else if (color == WHITE) {
			edge->setType(TREE_EDGE);
			dfs(*edge->getEnd());
		}
	}

	clock++;
	start.setColor(BLACK, clock);
}

void Graph::dfs(Node& start, Node& finish) {
// implement me. see header file for info.
}

void Graph::bfs(Node& start) {
// implement me. see header file for info.
}

void Graph::bfs(Node& start, Node& finish) {
// implement me. see header file for info.
}

Node::Node(string s) {
	data = s;
}

Node::~Node() {
// This is equivalent to the default destructor the compiler will
// generate for you. As a rule of thumb, you only need to `delete`
// member variables that were created with `new` inside this
// class. So, you don't need to do anything here. It could have been
// left out of the header/impl file entirely.
}

string Node::getData() {
	return data;
}

void Node::setRank(int r) {
	rank = r;
}

/**
 * Set the color to WHITE, the discovery/finish time and rank to -1,
 * and sets the predecessor to NULL.
 **/
void Node::clear() {
	this->color = WHITE;
	this->discovery_time = -1;
	this->completion_time = -1;
	this->rank = -1;
	this->predecessor = NULL;
}

void Node::setColor(int search_color, int time) {
	this->color = search_color;
	if (search_color == GRAY) {
		this->discovery_time = time;
	} else if (search_color == BLACK) {
		this->completion_time = time;
	}
}

void Node::getDiscoveryInformation(int& color, int& disco_time,
		int& finish_time, int& bfs_rank) {
// color is the parameter
// this-> is the member variable
	color = this->color;
	disco_time = this->discovery_time; // this is not necessary :)
	finish_time = completion_time;
	bfs_rank = rank;
}

bool Node::isAncestor(Node& other) {
	if (this->predecessor == &other) {
		return true;
	}
	return false;
}

void Node::setPredecessor(Node& other) {
	this->predecessor = &other;
}

Edge::Edge(Node& n1, Node& n2) {
	a = &n1;
	b = &n2;
	weight = 1.0;
}

Edge::~Edge() {
}

float Edge::getWeight() {
	return weight;
}

void Edge::setWeight(float val) {
	weight = val;
}

Node* Edge::getStart() {
	return a;
}

Node* Edge::getEnd() {
	return b;
}

int Edge::getType() {
	return type;
}

void Edge::setType(int edge_type) {
	type = edge_type;
}

string what(int& v) {
// HINT: Make use of this debugging function!
	string ret = "Unknown";
	if (v == WHITE) {
		ret = "White";
	} else if (v == GRAY) {
		ret = "Gray";
	} else if (v == BLACK) {
		ret = "Black";
	} else if (v == UNDISCOVERED_EDGE) {
		ret = "Undiscovered";
	} else if (v == TREE_EDGE) {
		ret = "Tree";
	} else if (v == BACK_EDGE) {
		ret = "Back";
	} else if (v == FORWARD_EDGE) {
		ret = "Forward";
	} else if (v == CROSS_EDGE) {
		ret = "Cross";
	}
	return ret;
}

ostream &operator <<(ostream& out, Graph graph) {
	out << graph.nodes.size() << " Nodes:" << endl;
	out << "[";
	for (vector<Node*>::iterator it = graph.nodes.begin();
			it != graph.nodes.end(); it++) {
		Node* n = *it;
		out << *n << ", ";
	}
	out << "]" << endl;
	out << graph.edges.size() << " Edges:" << endl;
	out << "[";
	for (vector<Edge*>::iterator it = graph.edges.begin();
			it != graph.edges.end(); it++) {
		Edge* e = *it;
		out << *e << ", ";
	}
	out << "]";
	return out;
}

ostream &operator <<(std::ostream& out, Node node) {
	out << node.data << " color: " << node.color << " dt/ft: "
			<< node.discovery_time << "/" << node.completion_time;
	return out;
}

ostream &operator <<(std::ostream& out, Edge edge) {
	out << *edge.a << " -- " << *edge.b << " (" << edge.type << ")";
	return out;
}

