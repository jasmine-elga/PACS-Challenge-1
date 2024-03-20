#include <functional>
#include<iostream>
#include<vector>
#include<cmath>
#include "minimum.hpp"




int main() {
    // Example usage
    Params params;
    
    std::function<double(const std::vector<double>&)> func = [](const std::vector<double>& x) {
        return x[0] * x[1] +  4 * std::pow(x[0],4)  +  std::pow(x[1],2) + 3 * x[0];
    };

    std::function<std::vector<double>(const std::vector<double>&)> grad_func = [](const std::vector<double>& x) {
        return std::vector<double>{x[1] + 16 * std::pow(x[0],3) + 3, x[0] + 2 * x[1]};
    };

    auto minimum = computeMinimum(func, grad_func, params);
    std::cout << "Minimum at (" << minimum[0] << ", " << minimum[1] << ")" << std::endl;
    std::cout << "Minimum is: "<< func(minimum) << std::endl;


    return 0;

}
