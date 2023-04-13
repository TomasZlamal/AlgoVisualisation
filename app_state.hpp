#pragma once
#include "algo.hpp"
#include "BFS.hpp"
namespace algo {
constexpr int genesis_point = 376;
class AppState {
	AppState(){
		changeAlgo<BFS_ALL_NODES>();
	}
	Algorithm* algo;
public:
	bool appChanged = 0;
	int time = 0;
	int speed_factor = 1;
	std::vector<Node*> nodes;
	static AppState* getInstance() {
		static AppState* instance = new AppState();
		return instance;
	}
	void appNext() {
		if (algo) {
			algo->next(nodes);
		}
	}
	void init(int genesis) {
		algo->init(genesis);
	}
	bool algoIsDone() {
		return algo->isDone();
	}
	template <typename T>
	void changeAlgo() {
		if(algo)
			delete algo;
		algo = new T{};
	}
}; 
#define ALGORITHM(x) algo::AppState::getInstance()->changeAlgo<x>();
}
