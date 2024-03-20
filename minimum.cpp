#include "minimum.hpp"
#include <cmath>
#include<iostream>


// Function to compute norm of a vector
double vectorNorm(const std::vector<double>& v) {
    double norm = 0.0;
    for (double value : v) {
        norm += value * value;
    }
    return std::sqrt(norm);
}


// Function to compute minimum
std::vector<double> computeMinimum(const std::function<double(const std::vector<double>&)>& f,
                                   const std::function<std::vector<double>(const std::vector<double>&)>& gradient,
                                   const Params& params) {
                                    int k = 0;
                                    auto current = params.x0;
                                    auto previous = current;                                  
                                    auto alpha = params.alpha0;
                                    auto sigma = params.sigma;

                                    bool converged = false;
                                    std::vector<double> grad;

                                    do{
                                        ++k;
                                        previous = current;
                                        
                                        //double mu = 0.01;
                                        //alpha *= std::exp(-mu*k); // exponential decay

                                        grad = gradient(previous);
                                        std::vector<double> dx(current.size(), 0.0);

                                        // Armijo line search
                                        while (true) {
                                            for (size_t i = 0; i < current.size(); ++i) {
                                                current[i] = previous[i] - alpha * grad[i];
                                                dx[i] = -alpha * grad[i];
                                            }
                                            double f_current = f(previous);
                                            double f_next = f(current);

                                            if (f_current - f_next >= sigma * alpha * vectorNorm(grad) * vectorNorm(grad)) {
                                                break; // Armijo condition satisfied
                                            } else {
                                                alpha *= 0.5; // Backtrack the step size
                                            }
                                        }

                                        converged = ( vectorNorm(dx) < params.eps_s) ; // || (vectorNorm(grad) < params.eps_r);
                                        std::cout << "dx norm: " << vectorNorm(dx)<< " alpha_k " << alpha << std::endl;
                                        std::cout << "iteration "<< k << " current = (" << current[0] << ", " << current[1] << ")" << std::endl; 
                                    }
                                    while((!converged) && (k<=params.maxIterations));

                                    return current;

                                   }


