#include "NuralNetwork.h"
#include <iostream>
#include <math.h>

void nn::NeuralNetwork::sigmoid(Eigen::MatrixXd & input)
{
	/*
	int size = input.array().size();
	double * a = input.data();
	Eigen::MatrixXd tmp(input.rows(), input.cols());
	for (int i = 0; i < size/8 + 1; i++) {
		
	}
	*/
	
	for (int r = 0; r < input.rows(); r++) {
		for (int c = 0; c < inputs.cols(); c++) {
			input(r, c) = 1.0f / (1 + std::pow(2.7182818284f, -input(r, c)));
		}
	}
	
}

double nn::NeuralNetwork::pow2(double x)
{
	return x*x;
}

void nn::NeuralNetwork::loadInputs()
{
	bool rand1 = std::rand() % 2;
	inputs(0, 0) = rand1 * 1.0f;
	inputs(1, 0) = (!rand1) * 1.0f;
}

nn::NeuralNetwork::NeuralNetwork(std::vector<int>& layerSizes)
{
	networkLayerSizes = layerSizes;
	std::cout << "Creating neural network...\n\n";
	// 2 3 2
	if (layerSizes.size() < 3) { std::cout << "Incrorrect input size\n"; return; }
	inputs = Eigen::MatrixXd(layerSizes[0], 1);
	inputs.setOnes();
	Eigen::MatrixXd b(layerSizes[1], layerSizes[0]);
	b.setOnes();
	weights.push_back(Eigen::MatrixXd(layerSizes[1], layerSizes[0]));
	weights[0].setRandom();
	weights[0] += b;
	weights[0] *= 0.5f;
	//std::cout << "Weight 0 = \n" << weights[0] << "\n";
	for (int i = 1; i < layerSizes.size() - 1; i++) {
		weights.push_back(Eigen::MatrixXd(layerSizes[i + 1], layerSizes[i]));
		weights[i].setRandom();
		Eigen::MatrixXd a(layerSizes[i + 1], layerSizes[i]);
		a.setOnes();
		weights[i] += a;
		weights[i] *= 0.5f;
		//std::cout << "Weight " << i << " = \n" << weights[i] << "\n";
	}
}

bool nn::NeuralNetwork::testIfCorrect()
{
	//Calculating output values
	Eigen::MatrixXd c(2, 2), d(2, 2);
	Eigen::MatrixXd nextLayer = weights[0] * inputs;
	sigmoid(nextLayer);
	for (int i = 1; i < networkLayerSizes.size() - 1; i++) {
		nextLayer = weights[i] * nextLayer;
		sigmoid(nextLayer);
	}
	bool isFirstInputLarger = inputs(0, 0) > inputs(1, 0);
	bool isFirstOutputLarger = nextLayer(0, 0) > nextLayer(1, 0);
	return (isFirstInputLarger == isFirstOutputLarger);
}

double nn::NeuralNetwork::evaluate()
{
	//Calculating output values
	Eigen::MatrixXd c(2, 2), d(2, 2);
	Eigen::MatrixXd nextLayer;
	nextLayer.noalias() = weights[0] * inputs;
	sigmoid(nextLayer);
	for (int i = 1; i < networkLayerSizes.size() - 1; i++) {
		nextLayer = weights[i] * nextLayer;
		
		sigmoid(nextLayer);
	}
	//Loss function:
	Eigen::MatrixXd preferedValues(nextLayer.rows(),1);
	if (inputs(0,0) < inputs(1,0)) {
		preferedValues(0, 0) = 0;
		preferedValues(1, 0) = 1;
	}
	else {
		preferedValues(0, 0) = 1;
		preferedValues(1, 0) = 0;
	}

	Eigen::MatrixXd dif;
	dif.noalias() = nextLayer - preferedValues;
	dif = dif.array().pow(2);
	

	return dif.sum();
}

void nn::NeuralNetwork::trainModel(int timesToTrain)
{
	double trainStepSize = 0.01;
	for (int i = 0; i < timesToTrain; i++) {
		for (int s = 0; s < weights.size(); s++) {
			for (int r = 0; r < weights[s].rows(); r++) {
				for (int c = 0; c < weights[s].cols(); c++) {
					double startVal = weights[s](r, c); // kanske fungerear?
					double leftVal =  weights[s](r, c) - trainStepSize;
					double rightVal = weights[s](r, c) + trainStepSize;
					double startErr = 0.0;
					double leftErr =  0.0;
					double rightErr = 0.0;

					//calculate avrage drivate for lots of inputs...
					for (int in = 0; in < 100; in++) {
						loadInputs();

						//Test left adjustmnt
						weights[s](r, c) = leftVal;
						leftErr += evaluate();

						//Test right adjustmnt
						weights[s](r, c) = rightVal;
						rightErr += evaluate();

						//Test original vals
						weights[s](r, c) = startVal;
						startErr += evaluate();

					}
					startErr /= 100.0;
					leftErr  /= 100.0;
					rightErr /= 100.0;

					double tangent;
					tangent = (leftErr - rightErr) / (2 * trainStepSize);
					weights[s](r, c) = startVal + (tangent * trainStepSize);
				}
			}
		}
	}
}
