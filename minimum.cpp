#include "minimum.hpp"
#include <cmath>

// Template function to compute minimum
template<Strategy S>
std::vector<double> computeMinimum(const func_t & f, const grad_t & gradient, const Params& params) {
                                    int k {0}; // iterations
                                    auto current = params.x0; // starting point
                                    auto previous = current;  // previous x               
                                    bool converged = false;
                                    double alpha;


                                    do{
                                        ++k; // increase number of iterations
                                        previous = current; // update previous point
                                        
                                        // Determine alpha based on the selected strategy
                                        if constexpr (S == Strategy::ExponentialDecay) {
                                            alpha =  ExponentialDecay(params, k);
                                        } else if constexpr (S == Strategy::InverseDecay) {
                                            alpha = InverseDecay(params, k);
                                        } else if constexpr (S == Strategy::Armijo) {
                                            alpha = Armijo(params, current, f, gradient);
                                        } else {
                                            std::cout << "INVALID STRATEGY!" << std::endl;
                                            return current;
                                        }
                                        current = current - alpha*gradient(current);
                                        converged = (vectorNorm(current-previous) < params.eps_s) || (vectorNorm(gradient(current)) < params.eps_r); // convergence criteria
                                    }
                                    while((!converged) && (k<=params.maxIterations));
                                    if (k<params.maxIterations){
                                        std::cout << "\n Gradient descend converged in "<< k << " iterations."<< std::endl;
                                    }
                                    else {
                                         std::cout << "\n Gradient descend NOT converged after "<< k << " iterations."<< std::endl;
                                    }
                                    return current;
                                   }



/// Explicit template instantiation for Armijo strategy
template std::vector<double>  computeMinimum<Strategy::Armijo>(const func_t & f, const grad_t & gradient, const Params& params);
/// Explicit template instantiation for ExponentialDecay strategy
template std::vector<double>  computeMinimum<Strategy::ExponentialDecay>(const func_t & f, const grad_t & gradient, const Params& params);
/// Explicit template instantiation for InverseDecay strategy
template std::vector<double> computeMinimum<Strategy::InverseDecay>(const func_t & f, const grad_t & gradient, const Params& params);



// Compute approximation of gradient via centered differences
std::vector<double> CenteredDifferences(double h, const func_t& f, const std::vector<double>& x) {
    // Dimension of the space
    std::vector<double> gradient(x.size());

    for (size_t i = 0; i < x.size(); ++i) {
        std::vector<double> x_plus = x;
        std::vector<double> x_minus = x;
        x_plus[i] += h;
        x_minus[i] -= h;

        gradient[i] = (f(x_plus) - f(x_minus)) / (2 * h);
    }
    return gradient;
}


    

// Compute alpha according to exponential decay strategy
double ExponentialDecay(const Params& params, int k){
   double alpha =  params.alpha0;
   return alpha*std::exp(-params.mu * k);
}

// Compute alpha according to inverse decay strategy
double InverseDecay(const Params& params, int k){
    return params.alpha0/(1+params.mu*k);
}

// Armijo rule for linear search
double Armijo(const Params& params, std::vector<double> & x, const func_t & f, const grad_t & grad){
        double alpha = params.alpha0;
        while (!DecreaseCondition(x, f, grad, alpha, params.sigma)) {
        alpha /= 2; // Reduce step size
    }
    return alpha; 
}

// Decrease condition for Armijo rule
bool DecreaseCondition( const std::vector<double> & x, const func_t & f , const grad_t & grad, double alpha, double sigma) {
    return f(x) - f(x-alpha*grad(x)) >= sigma *alpha * pow_integer(vectorNorm(x), 2);
}



// Compute the power (taken from lab, as std::pow() is expensive)
double pow_integer(double base, int exp) {
  double res = 1.0;
  while (exp > 0) {
    if (exp & 1)
      res *= base;
    base *= base;
    exp >>= 1;
  }
  return res;
}


// Function to compute norm of a vector
double vectorNorm(const std::vector<double>& v) {
    double norm = 0.0;
    for (double value : v) {
        norm += value * value;
    }
    return std::sqrt(norm);
}

// Operator- between 2 vectors
std::vector<double> operator-(const std::vector<double> v1, const std::vector<double> v2){
    std::vector<double> res=v1;
    for (size_t i=0; i<v1.size(); i++){
        res[i] = v1[i]-v2[i];
    }
    return res;
}

//Operator* between a scalar and a vector
std::vector<double> operator*(const double k, const std::vector<double> v){
    std::vector<double> res=v;
    for (size_t i=0; i<v.size(); i++){
        res[i] = k*v[i];
    }
    return res;
}