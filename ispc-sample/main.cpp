#include <iostream>
#include <cstdlib>
#include <vector>
// ISPC exported functions are included from a header created
// when running the ISPC compiler.
#include "sample_ispc.h"

int main(int argc, char **argv) {
	if (argc < 2) {
		std::cout << "Usage: " << argv[0] << " N [N vals] [N vals]\n";
		return 1;
	}
	const int nvals = std::atoi(argv[1]);
	if (argc != nvals * 2 + 2) {
		std::cout << "You must provide " << nvals
			<< " values for each list to add together\n";
		return 1;
	}
	std::vector<float> a(nvals, 0.f);
	std::vector<float> b(nvals, 0.f);
	std::vector<float> result(nvals, 0.f);
	for (int i = 0; i < nvals; ++i) {
		a[i] = std::atof(argv[i + 2]);
		b[i] = std::atof(argv[i + 2 + nvals]);
	}

	// In C++ the ISPC exported functions are in the ispc namespace
	ispc::multiply(a.data(), b.data(), result.data(), nvals);

	std::cout << "a * b  = [";
	for (size_t i = 0; i < result.size(); ++i) {
		std::cout << result[i];
		if (i + 1 < result.size()) {
			std::cout << ", ";
		}
	}
	std::cout << "]\n";
	return 0;
}

