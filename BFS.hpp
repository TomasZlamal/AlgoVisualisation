#pragma once
#include "all_node_algo.hpp"
#include "find_node_algo.hpp"
#include <queue>
namespace algo {
class BFS_ALL_NODES : public AllNodeAlgorithm {
	bool is_done;
	std::queue<int> nodes_to_visit;
public:
	BFS_ALL_NODES()
		: is_done(false) {
		
	}
	void init(int genesis) {
		nodes_to_visit.push(genesis);
	}
	void next(std::vector<Node*>& world) {
		if (nodes_to_visit.empty()) {
			is_done = true;
			return;
		}
		int curr = nodes_to_visit.front();
		nodes_to_visit.pop();
		if (world[curr]->type == kNodeType::Seen) {
			world[curr]->type = kNodeType::Marked;
		}
		for (int i = 0; i <= 3; i++) {
			int node_curr = moveAndGet(AllDirections[i], curr, world, meta::node_row_count);
			if (node_curr != -1 && world[node_curr]->type == kNodeType::Unmarked) {
				nodes_to_visit.push(node_curr);
				world[node_curr]->type = kNodeType::Seen;
			}
		}
	}
	bool isDone() {
		return is_done;
	}
	const char* getAlgoName() {
		return "Algorithm - BFS to visit all nodes";
	}
};
class BFS_FIND_NODE : public FindNodeAlgo {
	bool is_done;
	std::queue<int> nodes_to_visit;
public:
	BFS_FIND_NODE()
		: is_done(false) {

	}
	void init(int genesis) {
		nodes_to_visit.push(genesis);
	}
	void next(std::vector<Node*>& world) {
		if (nodes_to_visit.empty()) {
			is_done = true;
			return;
		}
		int curr = nodes_to_visit.front();
		nodes_to_visit.pop();
		if (world[curr]->type == kNodeType::Seen) {
			world[curr]->type = kNodeType::Marked;
		}
		for (int i = 0; i <= 3; i++) {
			int node_curr = moveAndGet(AllDirections[i], curr, world, meta::node_row_count);
			if (node_curr != -1) {
				if (world[node_curr]->type == kNodeType::Unmarked) {
					world[node_curr]->type = kNodeType::Seen;
					nodes_to_visit.push(node_curr);
				}
				if (world[node_curr]->type == kNodeType::Destination) {
					is_done = true;
					return;
				}
			}
		}
	}
	bool isDone() {
		return is_done;
	}
	const char* getAlgoName() {
		return "Algorithm - BFS to find a node";
	}
};
}