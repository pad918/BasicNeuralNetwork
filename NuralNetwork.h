#pragma once
#include <Eigen/Dense>
#include <Eigen/StdVector>
#include <Eigen/Core>
#include <vector>

namespace nn {

	class NeuralNetwork {
	private:
		std::vector<int> networkLayerSizes;
		Eigen::MatrixXd inputs;
		void sigmoid(Eigen::MatrixXd &input);
		std::vector<Eigen::MatrixXd> weights;
		//Functions
		double pow2(double x);
		
	public:
		NeuralNetwork(std::vector<int> &layerSizes);
		bool testIfCorrect(); // bara för test
		double evaluate();
		void trainModel(int timesToTrain);
		void loadInputs();
	};

}