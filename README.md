# About
This is an implementation of a genetic algorithm with floating point codes instead of bit codes.  
This significantly speeds up search, though it resembles random search a little more.
All genetic pooling and child rules are kept intact.
OpenMP is used to speed up population creation, fitness function evaluation, mating, etc.
Next step is probably to try this with CUDA.
# Usage
Create your objective and cost functions as function of the number of design variables a const float pointer to them.
Initialize the fitness functino with create_FitFunc() with a function pointer to the objective, the number of design variables, the pointer to the array, the number of >=, <=, and == constraints, and the last option is unused and will be GA_FALSE.
You can run a check on whether or not the fitness function is well formed with check_fitfuncOK().
Then call optimPop_Min() or optimPop_Max() depending on whether you are minimizing the objective of maximizing the objective.
After all that you should destroy the fitness function with destroy_FiFunc();
