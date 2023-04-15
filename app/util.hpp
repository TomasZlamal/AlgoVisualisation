#pragma once
#include <vector>
enum class kNodeType {
	Genesis,
	Unmarked,
	Marked,
	Seen,
	Destination
};
struct vec2 {
	int x, y;
};
struct Node {
	kNodeType type;
	vec2 pos;
};