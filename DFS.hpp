#pragma once
#include "all_node_algo.hpp"
#include "find_node_algo.hpp"
#include <stack>
namespace algo {
	class DFS_ALL_NODES : public AllNodeAlgorithm {
		bool is_done;
		std::stack<int> nodes_to_visit;
	public:
		DFS_ALL_NODES()
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
			int curr = nodes_to_visit.top();
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
	};
class DFS_FIND_NODE : public FindNodeAlgo {
	bool is_done;
	std::stack<int> nodes_to_visit;
public:
	DFS_FIND_NODE()
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
		int curr = nodes_to_visit.top();
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
		return "Algorithm - DFS to visit all nodes";
	}
};
}