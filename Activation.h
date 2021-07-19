//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"

#define  ACT_TYPE_ERR0R "Error: Activation type is not valid"
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

class Activation
{
 public:
  /**
   * Constructor - Inits new Activation with activation type
   */
   explicit Activation(ActivationType act_type);
  /**
   * @return this activation's type (ReLU/Softmax)
   */
  ActivationType get_activation_type() const;
  /**
   * Applies activation function on input, Does not change input.
   * @param input - the vector to apply activation function at.
   * @return copy to the new matrix - the result
   */
  Matrix operator()(const Matrix &input) const;


 private:
  ActivationType _act_type;
  /**
   * Relu - activation function that will output the input directly if it is
   * positive, otherwise, it will output zero.
   * @param vec - the vector to apply ReLu function at.
   * @param output - the vector to insert the result in.
   * @return reference to the output vector.
   */
  static void relu(const Matrix& vec, Matrix& output);
  /**
   * Softmax - activation function that converts a vector of numbers into a
   * vector of probabilities.
   * @param vec - the vector to apply Softmax function at.
   * @param output - the vector to insert the result in.
   * @return reference to the output vector.
   */
  static void softmax(const Matrix& vec, Matrix& output);
};

#endif //ACTIVATION_H
