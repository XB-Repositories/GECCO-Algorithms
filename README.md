# GECCO-Algorithms

Meta-heuristic algorithms used in "On the symmetry of the QAP through the Elementary Landscape Decomposition". The repository is composed of two directories:

- **LocalSearch:** Includes the Local Searh algorithm used in the estimation of the number of local optima.

- **MetaHeuristics:** Includes the two algorithms that are experimentally compared in the paper.
   - *Tabu Search.*
   - *Variable Function Search.*

All the algorithms are programmed in C. In order to execute each of them, enter the following commands in the Linux terminal:

- **Local Search**:
  ``` 
  > cd /path-to-repository/LocalSearch
  > make
  > ./CalculateLO {Instance path} {Repetition (seed)} {Objective function}
  ```
  The allowed objective function values are: 0 (f), 1 (f<sub>1</sub>), 2 (f<sub>2</sub>), 3 (f<sub>3</sub>). The results are printed in the following format:
  ``` Instance, Objective Function, Algorithm, Repetition, Solution, Fitness, Time ```
  
- **Tabu Search**:
  ``` 
  > cd /path-to-repository/MetaHeuristics/TabuSearch
  > make
  > ./TS {Instance path} {Repetition (seed)} {Tabu list size} {Number of evaluations}
  ```
  The results are printed in the following format:
  ``` Instance, Algorithm, Repetition, Solution, Fitness, Time ```

- **Variable Function Search**:
  ``` 
  > cd /path-to-repository/MetaHeuristics/VariableFunctionSearch
  > make
  > ./VFS {Instance path} {Repetition (seed)} {Tabu list size} {Number of evaluations}
  ```
  The results are printed in the following format:
  ``` Instance, Algorithm, Repetition, Solution, Fitness, Time ```
  
In all cases, the accepted instance format is the one used in [QAPLIB](https://www.opt.math.tugraz.at/qaplib/).
