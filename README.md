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

## Floating Point Chromosome Representation
- Chosen crossover strategy: crossover occurs at the resolution of design variables
- Mutation operation can be modeled as:

  𝑖𝑡ℎ𝑏𝑖𝑡=𝑟𝑎𝑛𝑑(0,𝑏𝑖𝑡𝑟𝑒𝑠)
  
  𝑣𝑎𝑙= (2^𝑖𝑡ℎ𝑏𝑖𝑡/2^𝑏𝑖𝑡𝑟𝑒𝑠 )(ub −lb)
  
  𝑚𝑢𝑡〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚={█(〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚+𝑣𝑎𝑙,  〖𝑏𝑖𝑡𝑠〗_(𝑐ℎ𝑟𝑜𝑚,𝐷𝑉,𝑖)=0@&〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚−𝑣𝑎𝑙,〖      𝑏𝑖𝑡𝑠〗_(𝑐ℎ𝑟𝑜𝑚,𝐷𝑉,𝑖)=1)┤
  
- Where bits_chrom,DV,i is calculated for the evaluation and not stored
- Chosen mutation strategy: mutation probability is evaluated at the resolution of design variables
- The chosen crossover and evaluating mutation per DV has the following probability distribution for f32 DVs:
- 
  〖𝑚𝑢𝑡𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚∼𝑟𝑎𝑛𝑑(〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚+𝑟𝑎𝑛𝑑(𝑙𝑏 −〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚, ub −〖𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚 ))
  
- Which can be further simplified to the following (with the chosen mutation strategy):

  𝑟𝑛𝑑𝑖𝑛𝑡~ 𝑟𝑎𝑛𝑑() % (2^𝑏𝑖𝑡𝑟𝑒𝑠+1)
  
  〖𝑚𝑢𝑡𝐷𝑉〗_𝑐ℎ𝑟𝑜𝑚=  𝑟𝑛𝑑𝑖𝑛𝑡/(2^𝑏𝑖𝑡𝑟𝑒𝑠−1) (𝑢𝑏 −𝑙𝑏)+𝑙𝑏**

## More settings and threading considerations
- DV bit resolution = 8
  - Max DV bit resolution would be = 15
    - RAND_MAX on my system = 2^15 – 1
- Population size = 100
- Crossover strategy: tournament 
- Mutation probability: 1 / ndv
- Independent Populations: 4
- Penalty scaling: 10

![image](https://user-images.githubusercontent.com/56926839/162248807-f810ae4d-aed8-4c2e-aa10-45eff63f02b6.png) 
![image](https://user-images.githubusercontent.com/56926839/162248822-e2b851e2-bed3-4816-92f3-22c23b9bf950.png)
![image](https://user-images.githubusercontent.com/56926839/162248822-e2b851e2-bed3-4816-92f3-22c23b9bf950.png)
![image](https://user-images.githubusercontent.com/56926839/162248901-0b14ccc6-42bc-4223-8c81-6121a94311ee.png)

## Example 1, p=20,000, std_dev_allow = 20,000, theta = 30 degrees, b1 = b3
![image](https://user-images.githubusercontent.com/56926839/162249357-6642068a-fea9-41e6-8dbf-ed403bc1b875.png)

Min of iter 5 is 2.699035 with: 0.862745, 0.258824,
Because of high population there is almost always:
Maximum & Minimum constraint violation in the population
All constraints satisfied at “optimal”
![image](https://user-images.githubusercontent.com/56926839/162249564-934f8bc7-0230-455a-87be-9405b667b64c.png)
![image](https://user-images.githubusercontent.com/56926839/162249591-1c7428e0-2a93-48bd-b0bf-0e77ce09bdf3.png)

## Example 2, p=20,000, std_dev_allow = 20,000, theta = 30 degrees, b1 = b3, alpha = .15
![image](https://user-images.githubusercontent.com/56926839/162249752-9b78a329-bf54-46c9-bbd7-e6bbc6da457a.png)
Min of iter 22 is 2.721918 with: 1.317647, 0.800000, 1.435294, 1.105882
Because of high population there is almost always:
Maximum & Minimum constraint violation in the population
All constraints satisfied at “optimal”
![image](https://user-images.githubusercontent.com/56926839/162249803-e3923940-bd21-46d4-9113-88fbe07c1179.png)
![image](https://user-images.githubusercontent.com/56926839/162249820-a18bca55-e79c-43b0-a975-0a30edc15bfd.png)

## Example 3, Sixe, Shape, and Topology, Failed FEA, p=20,000, std_dev_allow = 20,000, theta = 30 degrees, b1 = b3, alpha = .15, E = 10s*qrt(2)*20,000
![image](https://user-images.githubusercontent.com/56926839/162250072-e5c8110c-34e7-489e-8104-ea9c6a403894.png)
![image](https://user-images.githubusercontent.com/56926839/162250152-a00ad31d-6d8f-4e4e-9ece-8897a6547443.png)
![image](https://user-images.githubusercontent.com/56926839/162250183-42ba44b9-7192-4e9c-88e6-92fd7f01f2c8.png)

## Example 4, Transportation
![image](https://user-images.githubusercontent.com/56926839/162250274-9d99ae34-9080-43f9-9389-756ea91cf1d5.png)

## Example 4, Transportation with Binary Option
![image](https://user-images.githubusercontent.com/56926839/162250406-c25166cc-49c8-4ab8-818d-e24411cfa935.png)
![image](https://user-images.githubusercontent.com/56926839/162250369-32c8efd4-5409-4858-945f-e19f34faed2e.png)
![image](https://user-images.githubusercontent.com/56926839/162250429-9c1faccb-6a1b-4ecb-9e78-0af1322240fe.png)

## Example 5, Highly Non-linear
![image](https://user-images.githubusercontent.com/56926839/162250651-c9cb3392-4833-4e74-b7f1-516cbc7597be.png)
![image](https://user-images.githubusercontent.com/56926839/162250724-2d6ef35c-8ee5-4969-874f-5ebffba36a76.png)
![image](https://user-images.githubusercontent.com/56926839/162250743-9d1b02c6-1ee0-4e17-84d1-286b5000cb3a.png)
![image](https://user-images.githubusercontent.com/56926839/162250756-81f1674b-a353-4b44-a68f-a8d78208a820.png)







