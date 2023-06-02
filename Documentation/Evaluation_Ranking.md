**EVALUATION & RANKING:**

- The macro placement solution produced by participating placers will be evaluated using the Vivado© physical design compiler.  Contestant teams will be provided with a Vivado© license and a place-and-route flow that reads an input macro placement in the extended bookshelf format, check macro placement legality, and perform standard cell placement and routing.  The place-and-route flow will be non-timing driven for this contest.  The macro placement solution will be evaluated based on the following criteria:

  1.	Legality of the macro placement
  2.	Total routed wirelength, routing congestion
  3.	Macro placement runtime
  4.	Total placement and routing runtime of Vivado© place and route flow (5 hour limit)


-	There are 196 public benchmark designs provided (downloadable from https://www.kaggle.com/datasets/ismailbustany/mlcad2023-fpga-macroplacement-contest/settings?resource=download/)
- There are 44 hidden benchmark designs that will be shared after the conclusion of the contest.
- For each design in the benchmark suite (public or hidden), the macro placers will be ranked based on the contest evaluation metric. The final rank for a placer will be the sum of the individual ranks on all the circuits. The macro placer with the smallest total rank wins the contest.
- The macro placement runtime must be 10 minutes or less
- The macro placement must be legal.  That is, macros must be placed on their respective legal sites.
- The placement must be routable by the Vivado© router.  
- Vivado must complete the flow within 5 hours per design category. The run is considered failed if the place-and-route flow takes more than 5 hours to finish. 
-	The Vivado© router reports routing congestion metrics. This is the base of the score.
- The routing congestion metrics are composed of two parts:  An initial router metric and a detailed (final) router metric.
- **Initial Router Congestion Metric**: The initial router metric is presented as a table that captures short and global congestion in the north, south, east, and west directions (please see example table below):
```
INFO: [Route 35-449] Initial Estimated Congestion

|           | Global Congestion | Long Congestion   | Short Congestion  |
| Direction | Size   | % Tiles  | Size   | % Tiles  | Size   | % Tiles  |
|-----------|--------|----------|--------|----------|--------|----------|
|      NORTH|     2x2|      0.01|     8x8|      0.98|     1x1|      0.03|
|      SOUTH|     2x2|      0.01|     4x4|      1.27|     2x2|      0.02|
|       EAST|     4x4|      0.23|   16x16|      2.46|     2x2|      0.29|
|       WEST|     2x2|      0.43|   16x16|      3.49|     2x2|      0.58|

```
  - A level 2 initial router congestion is indicated by 2x2 in the above table. It means that a 2x2 grid of pixels in the interconnect fabric is congested and so on and so forth for levels 3, 4, ..., 8.
  - **Initial_routing_congestion_score** = 1.2 x sum(short_congestion_level_i^2 + sum(global_congestion_level_i^2), where i=north, south, east, and south.

 
 - **Final Router Congestion Metric:** The final router lists the intermediate number of congested wires (nodes with overlaps) during its iterations to resolve congestion (please see example below):
 
```
Phase 4 Rip-up And Reroute
Phase 4.1 Global Iteration 0
 Number of Nodes with overlaps = 94450
 Number of Nodes with overlaps = 6127
 Number of Nodes with overlaps = 197
 Number of Nodes with overlaps = 19
 Number of Nodes with overlaps = 4
 Number of Nodes with overlaps = 0
 ```
- **Final_routing_cong Score = number of iterations in Phase 4.1.
- **Routing_congestion_score = Initial_routing_congestion_score x Final_routing_congestion_score **

-	Total placement (macros and standard cells) and routing runtime will be used in computing P&R_Runtime_Factor;
-	Runtime_factor = (Total_runtime - Median_runtime) / 10.0 There is 1% scaling factor for every 10% runtime reduction/addition against the median runtime of all place+route solutions;
-	**Final_Score = Routing_congestion_score x (1 + Runtime_factor)**
-	The macro placement solution runtime should not take more than 10% of the overall place_and_route flow runtime.
-	We would like to stress that although runtime is a part of the contest metric, the "routing congestion metrics" will be the dominant component. In other words, a placer will not get a significant advantage if it is extremely fast compared to the median runtime of all the placers participating in the contest.
- The run corresponding to a failed place/route task will be assigned the lowest rank on this design. 
- In the presence of multiple failures, the break-tie factors are the following: Placer failure or router failure, router runtime, number of unrouted nets, number of illegal placements
