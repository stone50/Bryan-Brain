#pragma once

#include <vector>
#include <filesystem>
#include <fstream>

class Brain {
public:

	class InputNode {
	public:
		float value;
		float bias;
		std::vector<float> weights;

		InputNode();

		InputNode(
			const float _value,
			const float _bias,
			const std::vector<float> _weights
		);

		std::istream &read(std::istream &is);

		std::ostream &write(std::ostream &os);

		void randomize();
	};

	class MiddleNode {
	public:
		float value;
		float bias;
		float incomingValue;
		std::vector<float> middleWeights;
		std::vector<float> outputWeights;

		MiddleNode();

		MiddleNode(
			const float _value,
			const float _bias,
			const float _incomingValue,
			const std::vector<float> _middleWeights,
			const std::vector<float> _outputWeights
		);

		std::istream &read(std::istream &is);

		std::ostream &write(std::ostream &os);

		void randomize();
	};

	class OutputNode {
	public:
		float value;
		float incomingValue;

		OutputNode();

		OutputNode(
			const float _value,
			const float _incomingValue
		);

		std::istream &read(std::istream &is);

		std::ostream &write(std::ostream &os);

		void randomize();
	};

	Brain();

	Brain(const size_t inputs, const size_t middles, const size_t outputs);

	std::istream &read(std::istream &is);

	std::ostream &write(std::ostream &os);

	void randomize();

	void setInput(const size_t index, const float value);

	float getOutput(const size_t index);

	void think();

	// clears values and incoming values
	void reset();

	// loads the file into brain
	// returns true if the brain was successfully loaded
	static bool load(const std::filesystem::path &filepath, Brain& brain);

	// returns true if the brain was successfully saved
	bool save(const std::filesystem::path &filepath);

private:

	std::vector<InputNode> inputNodes;
	std::vector<MiddleNode> middleNodes;
	std::vector<OutputNode> outputNodes;

	float sigmoid(const float num);

	void sendInputsToMiddles();

	void sendMiddlesToMiddles();

	void sendMiddlesToOutputs();

	void calcMiddlesValues();

	void calcOutputValues();
};
