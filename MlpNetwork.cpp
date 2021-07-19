// MlpNetwork.cpp
#include "MlpNetwork.h"

/**
 * Constructor - Inits MlpNetwork with the given parameters
 * @param weights - array of 4 weights Matrix, one for each layer
 * @param biases - array of 4 biases Matrix, one for each layer
 */
MlpNetwork::MlpNetwork(Matrix weights[], Matrix biases[]):
           _layers{Dense(weights[0], biases[0], RELU),
                   Dense(weights[1], biases[1], RELU),
                   Dense(weights[2], biases[2], RELU),
                   Dense(weights[3], biases[3], SOFTMAX)}
                   // create the layers in the initialize member list
                   // cause Dense does not have default Ctor.
{}


/**
  * Applies the entire network on the input
  * @param input - the input vector - represents the image
  * @return digit struct
  */
digit MlpNetwork::operator()(const Matrix &input) const
{
  Matrix output_vec; // create output vector
  Matrix input_vec = input; // copy the input vector in order to change it
  for (const auto & layer : _layers)
    {
      // apply each layer on the current input vector
      output_vec = layer(input_vec);
      input_vec = output_vec; // update the input vector to the next layer
      // to be the output from the current layer
    }
  // initialize the first probability in the output vector to be the max.
  float max_prob = output_vec[0];
  unsigned int ind = 0;
  for (int i = 0; i < TEN; i++)
    {
      if (output_vec[i] > max_prob)
        {
          max_prob = output_vec[i]; // update the max probability if needed
          ind = i;
        }
    }
  return digit{ind, max_prob};
}