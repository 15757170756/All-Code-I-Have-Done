#include "tvf.h"
node operator+(const node &lhs, const node &rhs) {
	node ret(lhs);
	return ret += rhs;
}

node& node::operator+=(const node& rhs) {
	tensor[0] += rhs.tensor[0];
	tensor[1] += rhs.tensor[1];
	tensor[2] += rhs.tensor[2];
	tensor[3] += rhs.tensor[3];
	return *this;
}
node& node::operator=(const node &other) {
	tensor[0] = other.tensor[0];
	tensor[1] = other.tensor[1];
	tensor[2] = other.tensor[2];
	tensor[3] = other.tensor[3];
	return *this;
}
