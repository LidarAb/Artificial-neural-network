// Dense.cpp

#include "Dense.h"


/**
 * Inits a new layer with given parameters.
 * @param w - Matrix of weights
 * @param bias - matrix of bias
 * @param act_type - activation type
 */
Dense::Dense (Matrix &w, Matrix &bias, ActivationType act_type) :
    _activation (Activation (act_type))
// inits Activation in member list cause it does not have default ctor.
{
  _weights = w;
  _bias = bias;
}

// getters

Matrix Dense::get_weights () const
{
  return _weights;
}

Matrix Dense::get_bias () const
{
  return _bias;
}

Activation Dense::get_activation () const
{
  return _activation;
}

/**
 * Applies the layer on input and returns output matrix
 * @param input - the vector to apply  the layer on
 * @return output matrix
 */
Matrix Dense::operator() (const Matrix &input) const
{
  return _activation (_weights * input + _bias);
}
