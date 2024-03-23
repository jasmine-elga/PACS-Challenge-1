// documentation at https://github.com/nlohmann/json
#include "json.hpp"

#include <functional>
#include<iostream>
#include<vector>
#include<cmath>
#include <fstream>
#include "minimum.hpp"


int main(){
    // Define parameters
    Params params;

    // Extract parameters from json file and print them on
    using json = nlohmann::json;
    std::ifstream ifile("data.json");
    json j1;
    ifile >>j1;

    std::cout << "--- Parameters from file:" << std::endl;
    double x0 = j1.value("x0",0.0);
    double x1 = j1.value("x1",0.0);
    std::vector<double> x_init = {x0, x1};
    params.x0 = x_init;
    std::cout << "Initial guess: ( " << params.x0[0] << ", " << params.x0[1] <<  " )"<< std::endl;
    params.alpha0 = j1.value("alpha0", 0.1);
    std::cout << "initial alpha: " << params.alpha0 << std::endl;
    params.eps_s = j1.value("eps_s", 1e-6);
    std::cout << "esp_s (control on  step length): " << params.eps_s << std::endl;
    params.eps_r = j1.value("eps_r", 1e-6);
    std::cout << "esp_r  (control on residual) : " << params.eps_r << std::endl;
    params.maxIterations = j1.value("maxit", 10000);
    std::cout << "maximum n. of iterations: " << params.maxIterations << std::endl;
    params.sigma = j1.value("sigma", 0.3);
    std::cout << "sigma for Armijo rule: " << params.sigma << std::endl;
    params.h = j1.value("h", 0.3);
    std::cout << "h for centered difference gradient: " << params.h << std::endl;
    params.mu = j1.value("mu", 0.3);
    std::cout << "mu for exponential/inverse decay: " << params.mu << std::endl;
    std::cout << "---------------------------" << std::endl;

    
    // Define function 
    func_t func = [](const std::vector<double>& x) {
        // x1*x2 + 4*x1^4 + x2^2 + 3*x1 
        return x[0] * x[1] +  4 * pow_integer(x[0],4)  +  pow_integer(x[1],2) + 3 * x[0];
    };

    //Define gradient
    grad_t grad_func = [](const std::vector<double>& x) {
        return std::vector<double>{x[1] + 16 * pow_integer(x[0],3) + 3, x[0] + 2 * x[1]};
    };


    std::vector<double> minimum; // vector where the solution will be stored

    // Make user choose strategy from 
    int choice = 1;
    std::cout << "Choose optimization strategy:" << std::endl;
    std::cout << "1: Armijo Rule" << std::endl;
    std::cout << "2: Exponential Decay" << std::endl;
    std::cout << "3: Inverse Decay" << std::endl;
    std::cin >> choice;
 
    switch (choice) {
        case 1:
            std::cout << "You've choosen Armijo Rule.\n" << std::endl;
            minimum = computeMinimum<Strategy::Armijo>(func, grad_func, params);
            break;
        case 2:
            std::cout << "You've choosen Exponential decay.\n" << std::endl;
            minimum = computeMinimum<Strategy::ExponentialDecay>(func, grad_func, params);
            break;
        case 3:
            std::cout << "You've choosen Inverse decay.\n" << std::endl;
            minimum = computeMinimum<Strategy::InverseDecay>(func, grad_func, params);
            break;
        default:
            std::cerr << "Invalid choice!"<<std::endl;
            return 1;
    }
    
    std::cout << "Minimum at (" << minimum[0] << ", " << minimum[1] << ")" << std::endl;
    std::cout << "Minimum is: "<< func(minimum) << std::endl;
    
    return 0;

}
