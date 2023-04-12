#pragma once
#include "algo.hpp"
namespace algo {
class DFS : public Algorithm {
	bool mIsDone;
public:
	DFS()
		: mIsDone(false) {}
	void next(std::vector<Node*>& world) {

	}
	bool isDone() {
		return mIsDone;
	}
};
}