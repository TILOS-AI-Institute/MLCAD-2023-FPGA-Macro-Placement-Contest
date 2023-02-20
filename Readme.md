# MLCAD23-FPGA-Macro-Placement-Contest

____________________________________________________

**IEEE/ACM MLCAD 2023
FPGA MACROPLACEMENT CONTEST
CALL FOR PARTICIPATION**
____________________________________________________

**Registration start date:** TBD

**Registration deadline:** TBD

**GitHub site:** TBA

**E-mail:**  mlcad2023contest@gmail.com

   Macro placement plays an integral role in routability and timing closure for both the ASIC and FPGA physical design flows.  In particular, the discrete and columnated nature of the FPGA device layout presents unique placement constraints on placeable macros (e.g. BRAM’s, DSP’s, URAM’s, cascaded shapes, etc.).  These constraints are challenging for classical optimization and combinatorial approaches, and often the floorplans result in designs with routing and timing closure issues.  Inspired by recent deep reinforcement learning (RL) approaches (e.g. https://arxiv.org/abs/2004.10746), the goal of the competition is to spur academic research for developing ML or deep RL approaches to improve upon the current state-of-the-art macro placement tools.

**BENCHMARK DESCRIPTION:**
The organizers will provide a benchmark suite using enhanced bookshelf format.  Please refer to  https://github.com/TILOS-AI-Institute/MLCAD23-FPGA-Macro-Placement-Contest/tree/main/README for a full description of the file format.  Each design in the benchmark suite contains the following files:   

1.	design.nodes: Specifies placeable instances in the netlist (in Bookshelf format)
2.	design.nets: Specifies the set of nets in the netlist (in Bookshelf format)
3.	design.lib: Specifies the cell library for placeable objects
4.	design.pl: Specifies the site locations of the macros including cascaded macro shape instances, I/O, and fixed objects.   This supplied file only contains locations of fixed instances (IBUF/OBUF/BUFGCE etc). Your task is to supply the locations of the placeable macro instances. Valid locations for macro (and cascaded shape) instances are prescribed in the design.scl file.
5.	sample.pl:  Specifies a macro placement sample reference solution.
6.	design.scl:  Extended from the original bookshelf format to represent xcvu3p device layout and permissible site locations for all placeable object types (please refer to Figure 1).
7.	design.cascade_shape: Specifies the types of placeable cascaded macro shapes.
8.	design.cascade_shape_instances: Specifies the netlist instances of cascaded macro shapes.
9.	design.regions:  Specifies the box region constraints imposed on placeable objects
10.	design.dcp:  This file contains the synthesized netlist checkpoint that is required as an input by the Vivado© executable.
11.	place_route.tcl:   A TCL script to place and route a netlist using the Vivado© flow leveraging the input macro placement solution.

The FPGA architecture used in the contest will be based on an UltrascalePlus xcvu3p monolithic device //Does it makes sense to add a link here to the architectural description of the device? The organizers reserve the right to modify the contents of the benchmark designs and format.

**MACRO PLACEMENT EVALUTION:**
The macro placement solution produced by participating placers will be evaluated using the Vivado© physical design compiler.  Contestant teams will be provided with a Vivado© license and a place-and-route flow that reads an input macro placement in the extended bookshelf format, check macro placement legality, and perform standard cell placement and routing.  The place-and-route flow will be non-timing driven for this contest.  The macro placement solution will be evaluated based on the following criteria:

1.	Legality of the macro placement
2.	Global and detail routing metrics (within a time-out limit of 6 hours)
3.	Total routed wirelength, routing congestion
4.	Macro placement runtime
5.	Total placement and routing runtime of Vivado© place and route phases.

 
**Note:**  Teams are encouraged to develop a deep RL-based approach, but are free to use any approach (e.g. classical optimization, combinatorial, ML, RL, etc.) for their macro placement solution.


**RELEVANT CONTEST DATES:**
Please make note of the following dates:

- ${\color{red}03/10/2023}$: The test benchmark suite will be provided 
- 04/10/2023: To officially participate, contestants must register  
- 07/10/2023: Each team must submit an alpha binary submission for test purposes, else will be disqualified from the contest.
- 08/15/2023: Teams are required to submit their final executable binaries by 11:59pm (pacific time)
- 09/10/2023: The contest results will be announced during MLCAD 2023
 
**CONTEST REGISTRATION:**

- For registration and contest related inquiries, please email: mlcad2023contest@gmail.com
- Please add "MLCAD2023" to the subject line of any email.
- To register your team, please provide the following information:

1.	Affiliation of the team/contestant(s)
2.	Names of team members and advising professor
3.	One correspondence e-mail address for the team
4.	Name of the macro placer
5.	To participate in the contest and obtain a 1-year Vivado license, advising professors must register their team through the export compliant university program:  
https://www.xilinx.com/support/university/donation-program.html).

**PRIZES:**

Monetary prizes will be awarded to the top three teams.  More details on this will be announced on the web site.

**CONTEST COMMITTEE:**

Ismail Bustany (Chair)
Meghraj Kalase	 
Wuxi Li	 
Grigor Gasparyan	 
Amit Gupta
Andrew B. Kahng	 

**ACKNOWLEDGEMENTS:**

The organizers wish to thank Bodhisatta Pramanik, Zhiang Wang, Drs. Yuji Kukimoto, Sreevidya Maguluri, Ravishankar Menon, Nima Karimpour-Darav, Mehrdad Eslami, Chaithanya Dudha, Lin Chai, Kai Zhu, and Vishal Suthar for their helpful remarks, advice, and assistance.


**Evaluation & Ranking:**

-	There are 176 public benchmark designs provided (downloadable from https://www.kaggle.com/datasets/ismailbustany/mlcad2023-fpga-macroplacement-contest/settings)
- There are 60 hidden benchmark designs that will be shared after the conclusion of the contest.
- For each design in the benchmark suite (public or hidden), the macro placers will be ranked based on the contest evaluation metric. The final rank for a placer will be the sum of the individual ranks on all the circuits. The macro placer with the smallest total rank wins the contest.
- The macro placement runtime must 10 minutes or less
- The macro placement must be legal.  That is, macros must be placed on their respective legal sites.
- The placement must be routed by the Vivado© router.  The router must complete the job within 5 hours. The routing is considered failed if the router takes more than 5 hours to finish.
- Score = Routed-WL * (1 + Runtime_Factor)
o	The Vivado© router reports total routed wirelength. This is the base of the score.
o	Total placement (macros and standard cells) and routing runtime will be used in computing P&R_Runtime_Factor;
o	Runtime_Factor = - (Runtime - Median_Runtime) / 10.0 There is 1% scaling factor for every 10% runtime reduction/addition against the median runtime of all place+route solutions;
o	Runtime factor is between -10% and +10%
o	We would like to stress that although runtime is a part of the contest metric, the "Total Routed Wirelength" will be the dominant component. In other words, a placer will not get a significant advantage if it is extremely fast compared to the median runtime of all the placers participating in the contest.
- The run corresponding to a failed place/route task will be assigned the lowest rank on this design. 
- In the presence of multiple failures, the break-tie factors are the following: Placer failure or router failure, router runtime, number of unrouted nets, number of illegal placements
