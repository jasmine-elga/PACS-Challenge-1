#ifndef HH_MINIMUM_HH
#define HH_MINIMUM_HH
#include <vector>
#include<functional>


// Compute the norm of a vector.
/**
 * @param v : vector
 * 
*/
double vectorNorm(const std::vector<double>& v);


// Struct for parameters
struct Params {
    std::vector<double> x0 = {0.0, 0.0}; // initial guess
    double alpha0{0.2}; // initial step 
    double eps_s{1e-6}; // tolerance for step length
    double eps_r{1e-6}; // tolerance for residual
    int maxIterations{10000}; // maximum number of iterations
    double sigma{0.2}; // sigma for Armijo rule
};



// Compute the minimum of a multivariate function
/*
 @param f : multivariate function
 @param gradient: gradient of f
 @ param params: parameters for minimization
*/
std::vector<double> computeMinimum(const std::function<double(const std::vector<double>&)>& f,
                                   const std::function<std::vector<double>(const std::vector<double>&)>& gradient,
                                   const Params& params);
#endif

