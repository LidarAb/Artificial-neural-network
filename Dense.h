#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"

class Dense
{
 public:

  /**
   * Inits a new layer with given parameters.
   * @param w - Matrix of weights
   * @param bias - matrix of bias
   * @param act_type - activation type
   */
   Dense( Matrix& w, Matrix& bias, ActivationType act_type);

  // getters
  Matrix get_weights() const;
  Matrix get_bias() const;
  Activation get_activation() const;
  /**
   * Applies the layer on input and returns output matrix
   * @param input - the vector to apply  the layer on
   * @return output matrix
   */
  Matrix operator()(const Matrix &input) const;


 private:
  Matrix _weights;
  Matrix _bias;
  Activation _activation; // This filed is an Activation object represent
  // the activation function of the layer.
};

#endif //C___PROJECT_DENSE_H
