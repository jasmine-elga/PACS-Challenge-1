#ifndef HH_MINIMUM_HH
#define HH_MINIMUM_HH
#include <vector>
#include<iostream>
#include <functional>


// function wrapper for f 
using func_t= std::function<double(std::vector<double>)> ;
// function wrapper for gradient 
using grad_t= std::function<std::vector<double>(std::vector<double>)> ;

// Struct for parameters
struct Params {
    std::vector<double> x0; // initial guess
    double alpha0; // initial step 
    double eps_s; // tolerance for step length
    double eps_r; // tolerance for residual
    int maxIterations; // maximum number of iterations
    double sigma; // sigma for Armijo rule
    double h; // h for centered differences
    double mu; //mu for exponential/inverse decay
};


// enumerator for template parameter
enum class Strategy{
    Armijo,
    ExponentialDecay,
    InverseDecay
};


// Template function the minimum of a multivariate function 
template<Strategy S>
std::vector<double> computeMinimum(const func_t &, const grad_t &, const Params&); 

// Compute alpha according to Armijo rule
double Armijo(const Params&, std::vector<double> &, const func_t &, const grad_t & );
//Check condition for Armijo rule
bool DecreaseCondition( const std::vector<double> &, const func_t & , const grad_t &, double, double);

// Compute alpha according to exponential decay strategy
double ExponentialDecay(const Params& params, int k);

// Compute alpha according to inverse decay strategy
double InverseDecay(const Params &, int);



//grad_t FiniteDifferences(const func_t &f);


// Compute the power (taken from lab, as std::pow() is expensive)
double pow_integer(double base, int exp); 

// Compute the norm of a vector
double vectorNorm(const std::vector<double>& );

// Operator- between 2 vectors
std::vector<double> operator-(std::vector<double>, std::vector<double>);

//Operator* between a scalar and a vector
std::vector<double> operator*(const double k, const std::vector<double> v);




#endif //HH_MINIMUM_HH

