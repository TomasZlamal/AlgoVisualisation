#pragma once
#include "util.hpp"
#include "meta.hpp"
namespace algo {
enum class kDirection{
	Left,
	Right,
	Top,
	Down
};
enum class kAlgoType {
	AllNodes,
	Dest
};
const kDirection AllDirections[] = { kDirection::Left, kDirection::Top, kDirection::Right, kDirection::Down};
class Algorithm {
protected:
	virtual int moveAndGet(kDirection direction, int at, std::vector<Node*>& world, int row_node_count) final {
		switch (direction) {
		case kDirection::Top: {
			if (at-1 <= 0 || (at != 0 && at % row_node_count == 0)) {
				return -1;
			}
			return at - 1;
		} break;
		case kDirection::Down: {
			if (at+1 > world.size() || (at != 0 && (at+1) % row_node_count == 0)) {
				return -1;
			}
			return at + 1;
		} break;
		case kDirection::Right: {
			if ((at + row_node_count) >= world.size()) {
				return -1;
			}
			return at + row_node_count;
		} break;
		case kDirection::Left: {
			if ((at - row_node_count) < 0) {
				return -1;
			}
			return at - row_node_count;
		} break;
		default:
			return -1;
		}
	}
public:
	virtual void next(std::vector<Node*>& world) = 0;
	virtual bool isDone() = 0;
	virtual void init(int genesis) = 0;
	virtual kAlgoType getAlgoType() = 0;
	virtual const char* getAlgoName() = 0;
};
}