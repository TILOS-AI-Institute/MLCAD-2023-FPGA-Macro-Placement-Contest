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
 
The evaluation metrics on the github reporsitory has been updated accordingly.


Sample router solution output:
```  
Phase 3 Initial Routing
Phase 3.1 Global Routing
Phase 3 Initial Routing | Checksum: 20647d656
 
INFO: [Route 35-449] Initial Estimated Congestion
|-----------------------------------------------------------------------|
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

7.   ***Update to question regarding cascaded URAM Cascaded macros:***  (posted on 07/03/2023)
 
The following is based on questions about the cascade shape of URAM from Pu Yan and Andrew Guenter:
 
1. The URAM columns on the provided device is discrete, for the cascaded placement of URAMs, does it mean we have to place them on adjacent columns?
   
**Answer:**  We are removing the requirement that the Cascaded URAM macros need to be placed on adjacent columns.

2. The shape of URAM_CASCADE_8x2 is 8x2, does it mean that we have to place the first 8 URAMs on one column, and place the remaining 8 on another column?

**Answer:** No, please note that the placement of each URAM 8x1 subset can be on any valid URAM column sites, as long as each 8x1 subset is placed as a single discrete object.  That is, the two URAM 8x1 subsets can be placed next to each others on separate URAM site column, or on the same site column.  Also, the 8x1 subsets do not need to be placed on the same y-coordinates.   Please see an example of a valid placement for placing two URAM_CASCAD_8x2 macros (yellow and orange):

![URAM-8x2-cascade-placement](https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/assets/13140376/f4c67c0a-861d-4827-a429-8a1c8f0d8aed)

3. Each URAM Tile (as specified in desing.scl) contains 4 URAM sites.   For example,
```   
For example,  the cascaded 8x2 URAM instance below

URAM_CASCADE_8x2_inst_b/URAM288_inst1 48 120 0
URAM_CASCADE_8x2_inst_b/URAM288_inst2 48 120 1
URAM_CASCADE_8x2_inst_b/URAM288_inst3 48 120 2
URAM_CASCADE_8x2_inst_b/URAM288_inst4 48 120 3
URAM_CASCADE_8x2_inst_b/URAM288_inst5 48 135 0
URAM_CASCADE_8x2_inst_b/URAM288_inst6 48 135 1
URAM_CASCADE_8x2_inst_b/URAM288_inst7 48 135 2
URAM_CASCADE_8x2_inst_b/URAM288_inst8 48 135 3
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst10 48 90 1
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst11 48 90 2
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst12 48 90 3
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst13 48 105 0
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst14 48 105 1
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst15 48 105 2
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst16 48 105 3
URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst9 48 90 0
``` 
 is placed  as follows: 4 URAMs in tile (48,120), 4 URAMS on tile (48, 135), 4 URAMs on tile (48,90), and 4 URAMs on tile (48,105).


8. **Important Note about 8x2 URAM cascades** (posted on 07/05/2023)

      Upon some further deliberations, we have decided to exclude the designs with 8x2 cascaded URAMs from the benchmark suite.  Treating the structure of the columnar subsets as a  soft constraint  limits their utility for timing closure, and thus is an erroneous constraint specification on our part. My apologies for this error and the confusion this has caused you.  Thus, for now, please exclude the following designs from your evaluations:

```
1-clock:    
183,184,188,189,193,194,198,199,203,204,208,209,213,214,218,219,223,224
24-clocks: 
3,4,8,9,13,14,18,19,23,24,28,29,33,34,39,38,43,44,48,49
30-clocks: 
63,64,68,69,73,74,78,79,83,84,88,89,93,94,98,99,103,104
38-clocks: 
123,124,128,129,133,134,138,139,143,144,148,149,153,154,158,159

```
 
   We will augment the benchmark suite with additional designs to compensate for this deficit in the number of designs, and publish the new designs for your research purposes (but will not consider them when evaluating your macro placers). 


**9. Questions Nikhil @UBCPlaceM team** (posted on 07/13/2023)**

Question: We had a couple of questions about the number of clocks in design.
The designs provided to us have {1,24,30,38} clocks. Our preliminary analysis showed us that all clocks are of the same frequency. For example, in Design_3, all clocks have 7ns clock period. Could you confirm if this is the case for all designs in the benchmark suite (i.e. same clock period)? It would help us save a lot of time.

Answer: The clocks have the same frequency.  We have not varied the frequency requirements because the contest is non-timing driven.  The sole reason for introducing different number of clocks is to induce clock region constraints into the netlist.   W.r.t. runtime, that depends on other factors as well.  For instance, a design with 30 clocks may run faster than a design with 24 clocks if the 24-clock design has a higher Rents exponent, and so and so forth. 
many cases the run time for designs with 24 clocks have a higher runtime compared to the corresponding designs with 30 clocks. This seems counterintuitive. Could you please clarify how the number of clocks in a design affect the placement/routing? 

**Question:**  we’d really appreciate it if you could talk a bit more of the significance of the MLCAD2023_PublicBenchmakrSuiteDesignSpecifications.xlsx file in general.
    
**Answer:** The specification sheet shows how we constructed the designs.  We started out with a single design with a certain Rents exponent, then added various macro shapes, and dialed the Rents exponent and number of clocks. For instance, Designs 1-5 below have the same LUT, FF, RAM, DSP utilizations, number of clocks, and Rents exponent, but then we added cascaded macros to insances 2-5 of Design 1.  We followed this procedure in generating all the other designs in the benchmark suite.

```
Design Name 	LUT%	FF% 	RAMB%	DSP%	Input Rent	Number of Clocks	Vivado Runtime (s)		Notes
1	70	38	80	80	0.65	24	3148	0.87	No tall BRM/ DSP/ URAM/ Carries
2	70	38	80	80	0.65	24	3023	0.84	With 2 instances each of semi tall DSP and BRAM
3	70	38	80	80	0.65	24	3044	0.85	With 2 instances each of semi tall DSP, BRAM, URAM
4	70	38	80	80	0.65	24	3220	0.89	With 4 instances of semi tall (8x2) URAM
5	70	38	80	80	0.65	24	3572	0.99	With 4 instances each of tall DSP and BRAM ![image](https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/assets/13140376/932231c5-524b-476b-956e-2744214ff702)
```

**10. Questrion from Xinshi @CUMPLE team regardig congestion map** (posted on 07/15/2023)

**Question:** According to the definition, the congestion level is the site length of the smallest square. However, this is not the case for our contest designs. For example, the following is the interconnect congestion level obtained after routing in Design_2 (right-clicking in the Device window and selecting Metric > Interconnect Congestion Level). As highlighted with the red rectangle, this congestion area is the largest in this design and its level is 5. However, as we counted, the smallest rectangle to cover this region is about 57x71 and it is larger than the square (32x32) for level 5. Can you help investigate this? 
 
<img width="1541" alt="vivado-congestion-map" src="https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/assets/13140376/6fb27470-f01f-4021-8bd3-cd37b78d063f">
 

**Answer:**  For a given level k, It is the average congestion measured in the kxk square centered at a given interconnect time.   In the congestion map image you show, the orange colored tiles have congestion level 5 (32x32 squat per the explanation above) larger than the specific 0.9 routing resource utilization threshold in the GUI. The level 6 square (ie. 64x64) has centered at these tiles has resource utilization lower than the specified 0.9 threshold. Hence, these are marked as level 5.   


___________________________________________________________________________________________________________________________

**REPORTED BUGS IN THE BENCHMARK SUITE**
___________________________________________________________________________________________________________________________

**Bug#1. Please replace place_route.tcl with the the following version to get verbose output from Vivado:**  (posted on 06/02/2023) 
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
___________________________________________________________________________________________________________________________

 **Bug#2:  Fixed error in design.lib**  (posted on 06/15/2023)  
   The design.lib provided in the benchmark suite is missing a library definition.  Thanks to Hao Gu from team SEU_Placer for finding that bug.
Please use the version of design.lib posted on https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/tree/main/Benchmark_Suite instead of the version in the benchmark suite.
___________________________________________________________________________________________________________________________

 **Bug#3: Design_1 has a problem**   (posted on 06/15/2023)  
    Design_1 has a specification bug.  Please remove it from the benchmark suite.
___________________________________________________________________________________________________________________________

 **Bug#4: DSP macro names are incorrect in design.regions file**  (posted on06/28/2023)
    
    Many Thanks to Qin Luo from team CLUMP @CUHK for finding this bug.
    Please run the following csh script to fix errant DSP macro names in the design.regions file:
 
  ```
   % cd [path-to-your-benchmark-suite]
   % csh clean_regions.csh
```
   where clean_regions.csh is the following:
```
#!/bin/csh

foreach f (`ls */design.regions`)
    echo "editing $f"
    sed -i "s#/DSP_ALU_INST##g" $f
end
```
___________________________________________________________________________________________________________________________

**Bug#5:  Case sensitivity mismatch in Cascade objects names** (posted on 06/29/2023)

The correspondence of shape names in design.cascade_shape and design.cascade_shape_instances has a bug. The names of the Cascade object types should have the same letter case sensitivity, but they do not.  For instance, the attached image displays the files Design_2/design.cascade_shape on the left and Design_2/design.cascade_shape_instances on the right. The highlighted shape name on the right side should be modified to match the uppercase format of the corresponding shape on the left side.
	
![PastedGraphic-1](https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/assets/13140376/eefe7604-146f-4686-a6c7-6717a9a7c7fd)

Thanks to Jing Mai from team MPKU@Peking University for find this bug.

Please use this script to correct the error:

```
#!/bin/csh

foreach f (`ls */design.cascade_shape_instances`)

    echo "editing $f"

    sed -i "s#URAM_cascade_8x2#URAM_CASCADE_8x2#g" $f

    sed -i "s#BRAM_cascade#BRAM_CASCADE#g" $f

    sed -i "s#DSP_cascade#DSP_CASCADE#g" $f

end
```



___________________________________________________________________________________________________________________________

**Bug#6:  Please be aware that many of the sample.pl contain blocks with infeasible region constraints**
___________________________________________________________________________________________________________________________

**Bug#7:  Updating Benchmark suite on Kaggle**

-We are uploading an updated benchmark suite tonight (Kaggle https://www.kaggle.com/datasets/ismailbustany/updated-mlcad-2023-contest-benchmark.  The Kaggle uploading process is in progress.  It should be available in a couple of hours.

- Please use this updated benchmark suite in lieu of the current one

- It contains 140 designs.

- There are no 8x2 cascaded URAM macros since the placement support for them in the tool is not correct

- It includes fixes to bugs 1-7 reported by many of you and listed on https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/blob/main/Documentation/FAQ.md.

- We provided sample macro placement solutions only for designs with no region constraints 
That is, for 1-clock designs: Design_181 Design_182 Design_185 Design_186 Design_187 Design_190 Design_191 Design_192 Design_195 Design_196 Design_197 Design_200 Design_201 Design_202 Design_205 Design_206 Design_207 Design_210 Design_211 Design_212 Design_215 Design_216 Design_217 Design_220 Design_221 Design_222 Design_225 Design_226 Design_227 Design_230 Design_231 Design_232 Design_235 Design_236 Design_237 Design_240 without region constraints)

-For the remaining designs (i.e. designs with 24, 30, and 34 clocks), we do not provide sample solutions.  Instead we have added a new file, design.macros, that lists all the macro objects in that respective design (to know what macro objects it contains).

- We have updated the constraints in the file design.regions to fix a bug reported yesterday by Qin Luo from team CLUMP @CHHK (Thank you!). 

- Note: We are extending the final solution submission deadline from August 15, 2023 to August 20, 2023.
We will send further updates on this in subsequent e-mail messages, regarding a region checker utility.

- We greatly appreciate your engaging feedback, valuable questions, patience, and for finding and reporting these bugs.

________________________________________________________________________________________________________________________________________________________________________

**Bug#8: Error in design.cascaded_shape_instances file:** (Posted on 08/08/2023)

Please be aware of the following bug reported by Jing Mai from team MPKU at Peking University:
 
Upon reviewing design.cascaded_shape_instances, I noticed that the instances are not in the correct numerical order. Specifically, in the design.cascaded_shape_instances the instance numbers are listed as 1, 10, 2, 3, ..., 9. 


![cascaded_instance0](https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/assets/13140376/66343a45-15c7-4a8c-a54a-8bbb71e981a9)

Upon reviewing the file, I noticed that the instances are not in the correct numerical order. Specifically, in the design.cascaded_shape_instances the instance numbers are listed as 1, 10, 2, 3, ..., 9.  the design.nets file, the POUT pin of 

	DSP_CASCADE_10_inst_z/your_instance_name1/U0/i_synth/i_synth_option.i_synth_model/opt_8series.i_uniwrap/i_primitive
is connected to
	DSP_CASCADE_10_inst_z/your_instance_name2/U0/i_synth/i_synth_option.i_synth_model/opt_8series.i_uniwrap/i_primitive.

![cascaded_instance1](https://github.com/TILOS-AI-Institute/MLCAD-2023-FPGA-Macro-Placement-Contest/assets/13140376/b6c766eb-9eee-4582-a39e-712e59014bcb)

This discrepancy  occurred due to the instances being sorted alphabetically as strings, leading to the incorrect order.




