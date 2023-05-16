**1. How do I submit my macro placement solution?**

- Email your code to mlacd2023contest@gmail.com with the heading "MLCAD 2023 Solution Code"
- If your solution is completely in C++, you must provide source-cod, compilation, and execution instructions.
- If your solution uses python, you must provide a Docker container with a script that sets up your 
Python envirnoment, loads a benchmark design, and runs your macro-placer to generate a macroplacement, "solution.pl" 
file for us to evaluate.

**2. How does a sample macro placement solution file look like?**
- A sample macro placement solution file, sample.pl, is provided with each test case.  It is based on the ".pl" Bookshelf format.  Please inspect it to learn about the format.

**3. What Hardware acceleration platform can I use?**
You can use any hardware acceleration platform for training.  However, for us to evaluate your solution, you must provide a version that works on a CPU platform.

**4. What is the runtime requirement for generating the macro placement solution?**
The macro placement solution generation should not take more than 10% of the overall place_and_route flow runtime.
