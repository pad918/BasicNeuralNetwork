#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <chrono>
#include <Eigen/Dense>
#include "TriIRad.h"
#include "Matrix.h"
#include "NuralNetwork.h"

int main() {

	std::vector<int> sizes = {2, 3, 2};
	nn::NeuralNetwork net(sizes);
	
	auto a = net.evaluate();
	
	//std::cout << "\nOuput = \n" << a << "\n";
	/*for (int i = 0; i < 1000000; i++) // Debug: 1000 000 in 37755ms Release: 1000 000 in 583ms
		a = net.evaluate();
	*/
	double avgLoss = 0.0;
	int correct = 0;
	for (int i = 0; i < 100; i++) {
		net.loadInputs();
		avgLoss += net.evaluate();
		correct += 1 * net.testIfCorrect();
	}
	std::cout << "Avg err Before Training = " << avgLoss / 100.0 << "\n";
	std::cout << correct <<"/100 of test return correct before Training\n";
	auto start = std::chrono::high_resolution_clock::now();
	net.trainModel(1000); // 1000 times = 2910ms
	auto end = std::chrono::high_resolution_clock::now();
	avgLoss = 0.0;
	correct = 0;
	for (int i = 0; i < 100; i++) {
		net.loadInputs();
		avgLoss += net.evaluate();
		correct += 1 * net.testIfCorrect();
	}
	std::cout << "Avg err After Training = " << avgLoss / 100.0 << "\n";
	std::cout << correct << "/100 of test return correct after Training\n";
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	std::cout << "Time = " << duration.count() << "ms\n";
	int c;
	std::cin >> c;
	return 0;
}