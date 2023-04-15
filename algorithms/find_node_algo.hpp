#pragma once
#include "algo.hpp"
namespace algo{
class FindNodeAlgo : public Algorithm {
public:
	virtual kAlgoType getAlgoType() final {
		return kAlgoType::Dest;
	}
};
}