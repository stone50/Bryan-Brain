#pragma once

#include "Utils.h"

namespace Bryan {
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

			std::istream& read(std::istream& is);

			std::ostream& write(std::ostream& os);

			inline void randomize() {
				value = Utils::random();
				bias = Utils::random();
				for (size_t i = 0; i < weights.size(); i++) {
					weights[i] = Utils::random();
				}
			}
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

			std::istream& read(std::istream& is);

			std::ostream& write(std::ostream& os);

			inline void randomize() {
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

			std::istream& read(std::istream& is);

			std::ostream& write(std::ostream& os);

			inline void randomize() {
				value = Utils::random();
				incomingValue = Utils::random();
			}
		};

		Brain();

		Brain(const size_t inputs, const size_t middles, const size_t outputs);

		std::istream& read(std::istream& is);

		std::ostream& write(std::ostream& os);

		inline void randomize() {
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

		inline void setInput(const size_t index, const float value) {
			inputNodes[index].value = value;
		}

		inline float getOutput(const size_t index) {
			return outputNodes[index].value;
		}

		inline void think() {
			sendInputsToMiddles();
			sendMiddlesToMiddles();
			calcMiddleValues();
			sendMiddlesToOutputs();
			calcOutputValues();
		}

		// clears values and incoming values
		inline void resetState() {
			for (size_t i = 0; i < inputNodes.size(); i++) {
				inputNodes[i].value = 0;
			}

			for (size_t i = 0; i < middleNodes.size(); i++) {
				middleNodes[i].value = 0;
				middleNodes[i].incomingValue = 0;
			}

			for (size_t i = 0; i < inputNodes.size(); i++) {
				outputNodes[i].value = 0;
				outputNodes[i].incomingValue = 0;
			}
		}

		// loads the file into brain
		// returns true if the brain was successfully loaded
		static bool load(const std::filesystem::path& filepath, Brain& brain);

		// returns true if the brain was successfully saved
		bool save(const std::filesystem::path& filepath);

	private:

		std::vector<InputNode> inputNodes;
		std::vector<MiddleNode> middleNodes;
		std::vector<OutputNode> outputNodes;

		inline float sigmoid(const float num) {
			return atan(num);
		}

		inline void sendInputsToMiddles() {
			for (size_t i = 0; i < inputNodes.size(); i++) {
				for (size_t w = 0; w < inputNodes[i].weights.size(); w++) {
					middleNodes[w].incomingValue += inputNodes[i].value * inputNodes[i].weights[w] + inputNodes[i].bias;
				}
			}
		}

		inline void sendMiddlesToMiddles() {
			for (size_t i = 0; i < middleNodes.size(); i++) {
				for (size_t w = 0; w < middleNodes[i].middleWeights.size(); w++) {
					middleNodes[w].incomingValue += middleNodes[i].value * middleNodes[i].middleWeights[w] + middleNodes[i].bias;
				}
			}
		}

		inline void sendMiddlesToOutputs() {
			for (size_t i = 0; i < middleNodes.size(); i++) {
				for (size_t w = 0; w < middleNodes[i].outputWeights.size(); w++) {
					outputNodes[w].incomingValue += middleNodes[i].value * middleNodes[i].outputWeights[w] + middleNodes[i].bias;
				}
			}
		}

		inline void calcMiddleValues() {
			for (size_t i = 0; i < middleNodes.size(); i++) {
				middleNodes[i].value = sigmoid(middleNodes[i].incomingValue);
				middleNodes[i].incomingValue = 0;
			}
		}

		inline void calcOutputValues() {
			for (size_t i = 0; i < outputNodes.size(); i++) {
				outputNodes[i].value = sigmoid(outputNodes[i].incomingValue);
				outputNodes[i].incomingValue = 0;
			}
		}
	};
}