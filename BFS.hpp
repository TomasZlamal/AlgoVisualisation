#pragma once
#include "algo.hpp"
#include <queue>
namespace algo {
class BFS_ALL_NODES : public Algorithm {
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
};
}