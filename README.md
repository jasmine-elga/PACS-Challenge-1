# PACS-Challenge-1
## Gradient Descent Implementation
This repository contains an implementation of the gradient descent algorithm. 


The optimization parameters and the starting point are stored inside the ```data.json``` file:

```
{
    "x0": 0.0,
    "x1": 0.0,
    "alpha0": 0.2,
    "eps_s": 1e-6,
    "eps_r": 1e-6,
    "maxit": 10000,
    "sigma": 0.3,
    "h": 0.3,
    "mu": 0.3
  }

```

The strategy for the computation of the learning method can be chosen by the user from standard input, between:
* Armijo rule
* Exponential Decay
* Inverse Decay


For that purpose, a function template with an enumerator as a template parameter is implemented.

The function to minimize and its gradient are defined and can be modified in ```main.cpp```. 
The user can also decide from standard input whether to use the exact gradient or its approximation via central differences. 

The repo uses the library ```"json.hpp"```, defined inside the ```pacs-examples``` repository of the course.

The code is tested in the main on the function:

    $$ f(x) = f(x1,x2) = x_1x_2 +4x_1^4 +x_2^2 + 3x_1$$
