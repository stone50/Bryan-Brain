#pragma once

#include <Vector>
#include <filesystem>

class Brain
{
private:

	class InputNode {
	public:

		float value;
		float bias;
		std::vector<float> weights;

		InputNode(
			const float _value,
			const float _bias,
			const std::vector<float> _weights
		);

		void randomize();
	};

	class MiddleNode {
	public:

		float value;
		float bias;
		float incomingValue;
		std::vector<float> middleWeights;
		std::vector<float> outputWeights;

		MiddleNode(
			const float _value,
			const float _bias,
			const float _incomingValue,
			const std::vector<float> _middleWeights,
			const std::vector<float> _outputWeights
		);

		void randomize();
	};

	class OutputNode {
	public:

		float value;
		float incomingValue;

		OutputNode(
			const float _value,
			const float _incomingValue
		);

		void randomize();
	};

	std::vector<InputNode> inputNodes;
	std::vector<MiddleNode> middleNodes;
	std::vector<OutputNode> outputNodes;

	float sigmoid(const float num);

	void sendInputsToMiddles();

	void sendMiddlesToMiddles();

	void sendMiddlesToOutputs();

	void calcMiddlesValues();

	void calcOutputValues();

public:

	Brain(const size_t inputs, const size_t middles, const size_t outputs);

	void randomize();

	void SetInput(const size_t index, const float value);

	float GetOutput(const size_t index);

	void Think();

	// loads only the weights and biases of a brain from a file
	static Brain load(const std::filesystem::path& filepath);

	// loads the state of a brain from a file
	static Brain loadState(const std::filesystem::path& filepath);

	// saves only the weights and biases of the brain in a file
	void save(const std::filesystem::path& filepath);

	// saves the state of the brain in a file
	void saveState(const std::filesystem::path& filepath);
};

