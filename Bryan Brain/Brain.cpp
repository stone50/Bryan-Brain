#include <math.h>

#include "Utils.h"
#include "Brain.h"

#pragma region InputNode

Brain::InputNode::InputNode(
	const float _value,
	const float _bias,
	const std::vector<float> _weights
) :
	value(_value),
	bias(_bias),
	weights(_weights)
{};

void Brain::InputNode::randomize() {
	value = Utils::random();
	bias = Utils::random();
	for (size_t i = 0; i < weights.size(); i++) {
		weights[i] = Utils::random();
	}
}

#pragma endregion InputNode

#pragma region MiddleNode

Brain::MiddleNode::MiddleNode(
	const float _value,
	const float _bias,
	const float _incomingValue,
	const std::vector<float> _middleWeights,
	const std::vector<float> _outputWeights
) :
	value(_value),
	bias(_bias),
	incomingValue(_incomingValue),
	middleWeights(_middleWeights),
	outputWeights(_outputWeights)
{};

void Brain::MiddleNode::randomize() {
	value = Utils::random();
	bias = Utils::random();
	incomingValue = Utils::random();
	for (size_t i = 0; i < middleWeights.size(); i++) {
		middleWeights[i] = Utils::random();
	}
	for (size_t i = 0; i < outputWeights.size(); i++) {
		outputWeights[i] = Utils::random();
	}
}

#pragma endregion MiddleNode

#pragma region OutputNode

Brain::OutputNode::OutputNode(
	const float _value,
	const float _incomingValue
) :
	value(_value),
	incomingValue(_incomingValue)
{};

void Brain::OutputNode::randomize() {
	value = Utils::random();
	incomingValue = Utils::random();
}

#pragma endregion OutputNode

float Brain::sigmoid(const float num) {
	return atan(num);
}

void Brain::sendInputsToMiddles() {
	for (size_t i = 0; i < inputNodes.size(); i++) {
		for (size_t w = 0; w < inputNodes[i].weights.size(); w++) {
			middleNodes[w].incomingValue += inputNodes[i].value * inputNodes[i].weights[w] + inputNodes[i].bias;
		}
	}
}

void Brain::sendMiddlesToMiddles() {
	for (size_t i = 0; i < middleNodes.size(); i++) {
		for (size_t w = 0; w < middleNodes[i].middleWeights.size(); w++) {
			middleNodes[w].incomingValue += middleNodes[i].value * middleNodes[i].middleWeights[w] + middleNodes[i].bias;
		}
	}
}

void Brain::sendMiddlesToOutputs() {
	for (size_t i = 0; i < middleNodes.size(); i++) {
		for (size_t w = 0; w < middleNodes[i].outputWeights.size(); w++) {
			outputNodes[w].incomingValue += middleNodes[i].value * middleNodes[i].outputWeights[w] + middleNodes[i].bias;
		}
	}
}

void Brain::calcMiddlesValues() {
	for (size_t i = 0; i < middleNodes.size(); i++) {
		middleNodes[i].value = sigmoid(middleNodes[i].incomingValue);
		middleNodes[i].incomingValue = 0;
	}
}

void Brain::calcOutputValues() {
	for (size_t i = 0; i < outputNodes.size(); i++) {
		outputNodes[i].value = sigmoid(outputNodes[i].incomingValue);
		outputNodes[i].incomingValue = 0;
	}
}

Brain::Brain(const size_t inputs, const size_t middles, const size_t outputs) {
	inputNodes = std::vector<InputNode>(inputs, InputNode(
		0,								// value
		0,								// bias
		std::vector<float>(middles, 0)	// weights
	));
	middleNodes = std::vector<MiddleNode>(middles, MiddleNode(
		0,								// value
		0,								// bias
		0,								// incomingValue
		std::vector<float>(middles, 0),	// middleWeights
		std::vector<float>(outputs, 0)	// outputWeights
	));
	outputNodes = std::vector<OutputNode>(outputs, OutputNode(
		0,								// value
		0								// incomingValue
	));
}

void Brain::randomize() {
	for (size_t i = 0; i < inputNodes.size(); i++) {
		inputNodes[i].randomize();
	}
	for (size_t i = 0; i < middleNodes.size(); i++) {
		middleNodes[i].randomize();
	}
	for (size_t i = 0; i < outputNodes.size(); i++) {
		outputNodes[i].randomize();
	}
}

void Brain::SetInput(const size_t index, const float value) {
	inputNodes[index].value = value;
}

float Brain::GetOutput(const size_t index) {
	return outputNodes[index].value;
}

void Brain::Think() {
	sendInputsToMiddles();
	sendMiddlesToMiddles();
	calcMiddlesValues();
	sendMiddlesToOutputs();
	calcOutputValues();
}

// TODO
Brain Brain::load(const std::filesystem::path& filepath) {
	return Brain(0, 0, 0);
}

// TODO
Brain Brain::loadState(const std::filesystem::path& filepath) {
	return Brain(0, 0, 0);
}

// TODO
void Brain::save(const std::filesystem::path& filepath) {

}

// TODO
void Brain::saveState(const std::filesystem::path& filepath) {

}