#include "Activation.h"


/**
  * Constructor - Inits new Activation with activation type
  */
Activation::Activation (ActivationType act_type)
{
  if (act_type != RELU && act_type != SOFTMAX)
    {
      std::cerr << ACT_TYPE_ERR0R << std::endl;
      exit(EXIT_FAILURE);

    }
  _act_type = act_type;
}
/**
 * @return this activation's type (ReLU/Softmax)
 */
ActivationType Activation::get_activation_type() const
{
  return _act_type;
}

/**
 * Applies activation function on input, Does not change input.
 * @param input - the vector to apply activation function at.
 * @return copy to the new matrix - the result
 */
Matrix Activation::operator()(const Matrix &input) const
{
  Matrix output_vector = Matrix(input.get_rows(), input.get_cols());
  if (_act_type == RELU)
    {
      relu(input, output_vector);
      return output_vector;
    }
  else
    {
      softmax(input, output_vector);
      return output_vector;
    }
}

/**
 * Relu - activation function that will output the input directly if it is
 * positive, otherwise, it will output zero.
 * @param vec - the vector to apply ReLu function at.
 * @param output - the vector to insert the result in.
 * @return reference to the output vector.
 */
void Activation::relu(const Matrix& vec, Matrix& output)
{
  // apply ReLu function on each element in the vector.
  for (int i = 0; i < vec.get_rows() * vec.get_cols(); i++)
    {
      if (vec[i] < 0)
        {
          output[i] = 0;
        }
      else
        {
          output[i] = vec[i];
        }
    }
}

/**
 * Softmax - activation function that converts a vector of numbers into a
 * vector of probabilities.
 * @param vec - the vector to apply Softmax function at.
 * @param output - the vector to insert the result in.
 * @return reference to the output vector.
 */
void Activation::softmax(const Matrix& vec, Matrix& output)
{
  float sum = 0;
  // apply Softmax function on each element in the vector.
  for (int i = 0; i < vec.get_rows() * vec.get_cols(); i++)
    {
      sum += std::exp(vec[i]);
      output[i] = std::exp(vec[i]);
    }
  // the scalar to duplicate with the vector.
  float scalar = 1 / sum;
  output = output*scalar;
}
