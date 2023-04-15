#pragma once
#include "../algorithms/algo.hpp"
#include "../algorithms/BFS.hpp"
namespace algo {
class AppState {
	AppState(){
		changeAlgo<BFS_ALL_NODES>();
	}
	Algorithm* algo;
public:
	int time = 0;
	int speed_factor = 1;
	std::vector<Node*> nodes;
	static AppState* getInstance() {
		static AppState* instance = new AppState();
		return instance;
	}
	void resetNodes() {
		std::for_each(nodes.begin(), nodes.end(), [](Node* node) {node->type = kNodeType::Unmarked; });
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
	bool algoHasDestination() {
		return algo->getAlgoType() == kAlgoType::Dest;
	}
	template <typename T>
	void changeAlgo() {
		if(algo)
			delete algo;
		algo = new T{};
	}
	const char* getAlgoName() {
		return algo->getAlgoName();
	}
}; 
}
