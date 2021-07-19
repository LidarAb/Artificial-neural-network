//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Matrix.h"
#include "Dense.h"
#include "Activation.h"
#include "Digit.h"


#define MLP_SIZE 4
#define TEN 10

//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

class MlpNetwork
{
 public:
  /**
   * Constructor - Inits MlpNetwork with the given parameters
   * @param weights - array of 4 weights Matrix, one for each layer
   * @param biases - array of 4 biases Matrix, one for each layer
   */
  MlpNetwork(Matrix weights[], Matrix biases[]);
  /**
   * Applies the entire network on the input
   * @param input - the input vector - represents the image
   * @return digit struct
   */
  digit operator()(const Matrix &input) const;

 private:
  Dense _layers[MLP_SIZE];





};

#endif // MLPNETWORK_H
