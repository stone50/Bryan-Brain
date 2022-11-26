#include "Brain.h"

namespace Bryan {

	#pragma region InputNode

	Brain::InputNode::InputNode() :
		value(0),
		bias(0),
		weights(std::vector<float>())
	{}

	Brain::InputNode::InputNode(
		const float _value,
		const float _bias,
		const std::vector<float> _weights
	) :
		value(_value),
		bias(_bias),
		weights(_weights)
	{}

	std::istream& Brain::InputNode::read(std::istream& is) {
		is >> value;
		is >> bias;

		size_t weightCount;
		is >> weightCount;

		weights = std::vector<float>(weightCount);
		for (size_t i = 0; i < weightCount; i++) {
			is >> weights[i];
		}

		return is;
	}

	std::ostream& Brain::InputNode::write(std::ostream& os) {
		os << value << ' ';
		os << bias << ' ';

		os << weights.size() << ' ';
		for (size_t i = 0; i < weights.size(); i++) {
			os << weights[i] << ' ';
		}

		return os;
	}

	#pragma endregion InputNode

	#pragma region MiddleNode

	Brain::MiddleNode::MiddleNode() :
		value(0),
		bias(0),
		incomingValue(0),
		middleWeights(std::vector<float>()),
		outputWeights(std::vector<float>())
	{}

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
	{}

	std::istream& Brain::MiddleNode::read(std::istream& is) {
		is >> value;
		is >> bias;
		is >> incomingValue;

		size_t middleWeightCount;
		is >> middleWeightCount;

		middleWeights = std::vector<float>(middleWeightCount);
		for (size_t i = 0; i < middleWeightCount; i++) {
			is >> middleWeights[i];
		}

		size_t outputWeightCount;
		is >> outputWeightCount;

		outputWeights = std::vector<float>(outputWeightCount);
		for (size_t i = 0; i < outputWeightCount; i++) {
			is >> outputWeights[i];
		}

		return is;
	}

	std::ostream& Brain::MiddleNode::write(std::ostream& os) {
		os << value << ' ';
		os << bias << ' ';
		os << incomingValue << ' ';

		os << middleWeights.size() << ' ';
		for (size_t i = 0; i < middleWeights.size(); i++) {
			os << middleWeights[i] << ' ';
		}

		os << outputWeights.size() << ' ';
		for (size_t i = 0; i < outputWeights.size(); i++) {
			os << outputWeights[i] << ' ';
		}

		return os;
	}

	#pragma endregion MiddleNode

	#pragma region OutputNode

	Brain::OutputNode::OutputNode() :
		value(0),
		incomingValue(0)
	{}

	Brain::OutputNode::OutputNode(
		const float _value,
		const float _incomingValue
	) :
		value(_value),
		incomingValue(_incomingValue)
	{}

	std::istream& Brain::OutputNode::read(std::istream& is) {
		is >> value;
		is >> incomingValue;

		return is;
	}

	std::ostream& Brain::OutputNode::write(std::ostream& os) {
		os << value << ' ';
		os << incomingValue << ' ';

		return os;
	}

	#pragma endregion OutputNode

	Brain::Brain() :
		inputNodes(std::vector<InputNode>()),
		middleNodes(std::vector<MiddleNode>()),
		outputNodes(std::vector<OutputNode>())
	{}

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

	std::istream& Brain::read(std::istream& is) {
		size_t inputNodeCount;
		is >> inputNodeCount;

		inputNodes = std::vector<InputNode>(inputNodeCount);
		for (size_t i = 0; i < inputNodeCount; i++) {
			inputNodes[i].read(is);
		}

		size_t middleNodeCount;
		is >> middleNodeCount;

		middleNodes = std::vector<MiddleNode>(middleNodeCount);
		for (size_t i = 0; i < middleNodeCount; i++) {
			middleNodes[i].read(is);
		}

		size_t outputNodeCount;
		is >> outputNodeCount;

		outputNodes = std::vector<OutputNode>(outputNodeCount);
		for (size_t i = 0; i < outputNodeCount; i++) {
			outputNodes[i].read(is);
		}

		return is;
	}

	std::ostream& Brain::write(std::ostream& os) {
		os << inputNodes.size() << ' ';
		for (size_t i = 0; i < inputNodes.size(); i++) {
			inputNodes[i].write(os);
		}

		os << middleNodes.size() << ' ';
		for (size_t i = 0; i < middleNodes.size(); i++) {
			middleNodes[i].write(os);
		}

		os << outputNodes.size() << ' ';
		for (size_t i = 0; i < outputNodes.size(); i++) {
			outputNodes[i].write(os);
		}
		return os;
	}

	bool Brain::load(const std::filesystem::path& filepath, Brain& brain) {
		std::ifstream filestream(filepath, std::ifstream::binary);

		if (filestream.is_open()) {
			brain.read(filestream);

			filestream.close();

			return true;
		}

		return false;
	}

	bool Brain::save(const std::filesystem::path& filepath) {
		std::ofstream filestream(filepath, std::ofstream::binary);

		if (filestream.is_open()) {
			write(filestream);

			filestream.close();

			return true;
		}

		return false;
	}
}