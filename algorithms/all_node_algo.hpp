#pragma once
#include "algo.hpp"
namespace algo{
class AllNodeAlgorithm : public Algorithm {
public:
	virtual kAlgoType getAlgoType() final {
		return kAlgoType::AllNodes;
	}
};
}