# About
This is an implementation of a genetic algorithm with floating point codes instead of bit codes.  
This significantly speeds up search, though it resembles random search a little more.
All genetic pooling and child rules are kept intact.
OpenMP is used to speed up population creation, fitness function evaluation, mating, etc.

# Usage
Create your objective and cost functions as function of the number of design variables a const float pointer to them.
Initialize the fitness functino with create_FitFunc() with a function pointer to the objective, the number of design variables, the pointer to the array, the number of >=, <=, and == constraints, and the last option is unused and will be GA_FALSE.
You can run a check on whether or not the fitness function is well formed with check_fitfuncOK().
Then call optimPop_Min() or optimPop_Max() depending on whether you are minimizing the objective of maximizing the objective.
After all that you should destroy the fitness function with destroy_FiFunc();

# Floating Point Chromosome Representation
- Chosen crossover strategy: crossover occurs at the resolution of design variables
- Mutation operation can be modeled as:
  𝑖𝑡ℎ𝑏𝑖𝑡=𝑟𝑎𝑛𝑑(0,𝑏𝑖𝑡𝑟𝑒𝑠)
  𝑣𝑎𝑙= (2^𝑖𝑡ℎ𝑏𝑖𝑡/2^𝑏𝑖𝑡𝑟𝑒𝑠 )(ub −lb)
  𝑚𝑢𝑡〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚={█(〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚+𝑣𝑎𝑙,  〖𝑏𝑖𝑡𝑠〗_(𝑐ℎ𝑟𝑜𝑚,𝐷𝑉,𝑖)=0@&〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚−𝑣𝑎𝑙,〖      𝑏𝑖𝑡𝑠〗_(𝑐ℎ𝑟𝑜𝑚,𝐷𝑉,𝑖)=1)┤
- Where bits_chrom,DV,i is calculated for the evaluation and not stored
- Chosen mutation strategy: mutation probability is evaluated at the resolution of design variables
- The chosen crossover and evaluating mutation per DV has the following probability distribution for f32 DVs:
  〖𝑚𝑢𝑡𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚∼𝑟𝑎𝑛𝑑(〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚+𝑟𝑎𝑛𝑑(𝑙𝑏 −〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚, ub −〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚 ))
- Which can be further simplified to the following (with the chosen mutation strategy):
  𝑟𝑛𝑑𝑖𝑛𝑡~ 𝑟𝑎𝑛𝑑() % (2^𝑏𝑖𝑡𝑟𝑒𝑠+1)
  〖𝑚𝑢𝑡𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚=  𝑟𝑛𝑑𝑖𝑛𝑡/(2^𝑏𝑖𝑡𝑟𝑒𝑠−1) (𝑢𝑏 −𝑙𝑏)+𝑙𝑏**

- DV bit resolution = 8
  - Max DV bit resolution would be = 15
    - RAND_MAX on my system = 2^15 – 1
- Population size = 100
- Crossover strategy: tournament 
- Mutation probability: 1 / ndv
- Independent Populations: 4
- Penalty scaling: 10


