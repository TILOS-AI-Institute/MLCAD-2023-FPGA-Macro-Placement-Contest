**1. How do I submit my macro placement solution?**  (posted on 02/21/2023) 

- Email your code to mlacd2023contest@gmail.com with the subject "MLCAD 2023 Solution Code".
- If your solution is entirely in C++, you must provide source code, as well as compilation and execution instructions.
- If your solution uses Python, you must provide a Docker container with a script that sets up your Python environment, loads a benchmark design, and runs your macro placer to generate a macro placement solution file, "solution.pl," for us to evaluate.

**2. How does a sample macro placement solution file look like?**  (posted on 02/21/2023) 
A sample macro placement solution file, sample.pl, is provided with each test case.  It is based on the ".pl" Bookshelf format.  Please inspect it to learn about the format.

**3. What hardware acceleration platform can I use?**  (posted on 04/20/2023) 
You can use any hardware acceleration platform for training.  However, for us to evaluate your solution, you must provide a version that works on a CPU platform.

**4. What is the runtime requirement for generating the macro placement solution?**  (posted on 05/16/2023) 
The macro placement solution generation time should not take more than 10% of the overall place_and_route flow runtime.


 **5. Changes to score evaluation metrics:**  (posted on 06/02/2023) 
Many thanks to Leslie Pu (from team CUMP at CUHK) for finding several issues with the contest specifications.  Two of these issues are listed below:
 Vivado Verbose mode:   Please change the place_route.tcl file provided in each benchmark design as follows to add verbose mode:

place_design -macro_placement sample.pl  --> place_design -macro_placement sample.pl -verbose
route_design --> route_design -verbose

With this change, Vivado will generate a routing congestion report at the end of the run. 
Score Evaluation:  The routed wirelength will not be reported by Vivado.  Instead, various routing congestion metrics will be reported.  We will amend the routability score to be based solely on the congestion metrics and accordingly update the evaluation metrics.  You need to ensure the following:
1.  Initial global and short congestion levels are the lowest possible (these levels vary between 1-8).
2.  Initial short congestion level weighs more than initial global congestion level (multiplier factor is 1.2).     
3.  Minimize number of initial node overlaps (which indirectly reflects pin access issues)
4.  Minimize the number of iterations that phase 4.1 takes to converge when the design is routable (this correlates with the detailed router's runtime)
 
  I will amend the score evaluation metrics in the github documentation accordingly.

Best regards,
Ismail

Sample router solution output:
  
Phase 3 Initial Routing
Phase 3.1 Global Routing
Phase 3 Initial Routing | Checksum: 20647d656
 
INFO: [Route 35-449] Initial Estimated Congestion
```
|           | Global Congestion | Long Congestion   | Short Congestion  |
| Direction | Size   | % Tiles  | Size   | % Tiles  | Size   | % Tiles  |
|-----------|--------|----------|--------|----------|--------|----------|
|      NORTH|     2x2|      0.01|     8x8|      0.98|     1x1|      0.03|
|      SOUTH|     2x2|      0.01|     4x4|      1.27|     2x2|      0.02|
|       EAST|     4x4|      0.23|   16x16|      2.46|     2x2|      0.29|
|       WEST|     2x2|      0.43|   16x16|      3.49|     2x2|      0.58|
 
Congestion Report
  LONG Congestion bounded by tiles (Lower Left Tile -> Upper Right Tile):
EAST
        INT_X63Y179->INT_X78Y202 (CLEM_X63Y179->URAM_URAM_FT_X78Y195)
        INT_X64Y185->INT_X79Y200 (CLEM_X64Y185->CLEL_R_X79Y200)
        INT_X64Y184->INT_X79Y199 (CLEM_X64Y184->CLEL_R_X79Y199)
        INT_X64Y183->INT_X79Y198 (CLEM_X64Y183->CLEL_R_X79Y198)
        INT_X64Y181->INT_X79Y196 (CLEM_X64Y181->CLEL_R_X79Y196)
        
WEST
        INT_X69Y177->INT_X76Y200 (CLEM_X69Y177->CLEL_R_X76Y200)
        INT_X40Y228->INT_X47Y235 (CLEM_X40Y228->CLEL_R_X47Y235)
        INT_X40Y227->INT_X47Y234 (CLEM_X40Y227->CLEL_R_X47Y234)
        INT_X40Y226->INT_X47Y233 (CLEM_X40Y226->CLEL_R_X47Y233)
        INT_X32Y241->INT_X39Y248 (BRAM_X32Y240->DSP_X39Y245)

Phase 4 Rip-up And Reroute
Phase 4.1 Global Iteration 0
 Number of Nodes with overlaps = 94450
 Number of Nodes with overlaps = 6127
 Number of Nodes with overlaps = 197
 Number of Nodes with overlaps = 19
 Number of Nodes with overlaps = 4
 Number of Nodes with overlaps = 0
Phase 4.1 Global Iteration 0 | Checksum: 191c37161

Time (s): cpu = 00:19:53 ; elapsed = 00:06:47 . Memory (MB): peak = 9588.973 ; gain = 334.016 ; free physical = 18071 ; free virtual = 180276
Phase 4 Rip-up And Reroute | Checksum: 191c37161

Time (s): cpu = 00:19:54 ; elapsed = 00:06:49 . Memory (MB): peak = 9588.973 ; gain = 334.016 ; free physical = 18071 ; free virtual = 180276

Phase 5 Delay and Skew Optimization
Phase 5 Delay and Skew Optimization | Checksum: 1429a133d

Phase 6 Post Hold Fix
Phase 6.1 Hold Fix Iter
Phase 6.1 Hold Fix Iter | Checksum: 1429a133d

Phase 6 Post Hold Fix | Checksum: 1429a133d

Time (s): cpu = 00:20:00 ; elapsed = 00:06:54 . Memory (MB): peak = 9588.973 ; gain = 334.016 ; free physical = 18109 ; free virtual = 180313

Phase 7 Route finalize
Router Utilization Summary
  Global Vertical Routing Utilization    = 25.2538 %
  Global Horizontal Routing Utilization  = 31.4871 %
  Routable Net Status*
  *Does not include unroutable nets such as driverless and loadless..
  Run report_route_status for detailed report.
  Number of Failed Nets               = 0
    (Failed Nets is the sum of unrouted and partially routed nets)
  Number of Unrouted Nets             = 0
  Number of Partially Routed Nets     = 0
  Number of Node Overlaps             = 0
```

**6. Please replace place_route.tcl with the the following version to get verbose output from Vivado:**  (posted on 06/02/2023) 
```
############################## AMD Copyright (c) 2023 ##############################

#    Permission is hereby granted, free of charge, to any person obtaining a copy
#  of this software and associated documentation files (the "Software"), to deal
#  in the Software without restriction, including without limitation the rights
#  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
#  copies of the Software, and to permit persons to whom the Software is
#  furnished to do so, subject to the following conditions:
#
#    The above copyright notice and this permission notice shall be included in
#  all copies or substantial portions of the Software.
#
#    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
#  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
#  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
#  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
#  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
#  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
#  THE SOFTWARE.
#
####################################################################################

#Load the synthesized netlist
open_checkpoint ./design.dcp

set_param place.timingDriven false

#Place design using the bookshelf macro placement
place_design  -macro_placement sample.pl -verbose

#route design
route_design -no_timing_driven -verbose

#generate routing Report
report_route_status
```


7.   ***Question regarding cascaded URAM macros:***
  ```
Dear Sir or Madam,
Hello.
I have two questions about the cascade shape of URAM, which straddles two columns:

1. The URAM columns on the provided device is discrete, for the cascaded placement of URAMs, does it mean we have to place them on adjacent columns?
Answer:  Yes.

2. The shape of URAM_CASCADE_8x2 is 8x2, does it mean that we have to place the first 8 URAMs on one column, and place the remaining 8 on another column?
Answer: Yes.

Thanks a lot!
Best
Pu Yuan
```

8.  **Fixed error in design.lib**  (posted on 06/15/2023)  
   The design.lib provided in the benchmark suite is missing a library definition.  Thanks to Hao Gu from team SEU_Placer for finding that bug.
Please use the version of design.lib posted on https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/tree/main/Benchmark_Suite instead of the version in the benchmark suite.

9.  **Design_1 has a problem**   (posted on 06/15/2023)  
    Design_1 has a specification bug.  Please remove it from the benchmark suite.
