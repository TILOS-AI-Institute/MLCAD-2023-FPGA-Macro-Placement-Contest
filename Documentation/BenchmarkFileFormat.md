
------------------------------------------------------------------------------------
**Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:**

**The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.**

**THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.**

---------------------------------------------------------------------------------------

**File Format for the MLCAD 2023 FPGA Macro Placement Competition**
**(AMD copyright 2023)**

----------------------------------------------------------------------------------------

This document explains the features of the FPGA macro placement file format.  With the exception of 
the Vivado binary design checkpoint input file "design.dcp", it is based on an extension to the 
Bookshelf format.  


**1. design.nets:**  
   - This file describes the netlist connectivity in Bookshelf format

**2. design.nodes:**
   - This file describes the placeable object instances in the netlist in Bookshelf format.

**3. design.lib (Library cell):**
  - Each placeable object instance has a corresponding master library cell.
  - All library cells are defined in design.lib. 
  - All pins are defined in library file (.lib) cell section.
  - Each instance has the same number of pins as defined in its master cell.
  - Not all the pins of an instance are used. Some are left unconnected.
  - Library file defines certain attributes associated with pins: direction, clock, and control.
  - Each net is a collection of pins, as specified in nets file.
  - NOTE:  The format of this file is identical to that released in the ACM ISPD 2016 placement contest,
    http://www.ispd.cc/contests/16/ispd2016_contest.html

**4. design.scl (Device Layout)** 
  - This file specifies the device layout placement for all instance types.
  - There are two section in layout file: SITE definition section and SITE map section.
  - SITE definition specifies available resources (LUT/FF/RAMB/DSP) that can be placed in one site.
  - RESOURCES specifies cell names that correspond to certain resource.
  - SITE map specifies the two-dimension array of sites for the entire device/chip.
  - NOTE 1:  The format of this file is similar to that released in the ACM ISPD 2016 placement contest,
    http://www.ispd.cc/contests/16/ispd2016_contest.html
  - NOTE 2:  Different from the 2016 ISPD Placement, we use an UltraScalePlus device, xcvu3p, in this competition.
      

**5. design.pl (Locations of fixed instances and placeable macro instances)** 
  - This file lists the location of placeable macro instances in the netlist
  - The location of an instance has three fields: <Column_number> <Site_number>  <BEL_number> 
    The BEL number is the index within the SITE.  The BEL number for macro instances is always 0.
  - This supplied file only contains locations of fixed instances (IBUF/OBUF/BUFGCE etc).
    Fixed instance locations, including BEL numbers, are not allowed to change during placement.
  - NOTE 1: Your task is to supply the locations of the macro instances. Valid locations for
    macro (and cascaded shape) instances are prescribed in the design.scl file.  
  - NOTE 2: You can add the macro placement instances locations using the following format:

        <intance_name> <Column_number> <Site_number> <BEL_number>

        and as mentioned above <BEL_number> is always set to 0 for macro (and cascade shape) instances

        For example:    

          BRAM_config_BRAM_SDP_inst762_inst_b/my_sdpram 195 45 0
          BRAM_config_BRAM_SDP_inst762_inst_bb/my_sdpram 142 10 0
          DSP_config_DSP_inst31_inst_b/my_dsp 202 60 0
          DSP_config_DSP_inst31_inst_bb/my_dsp 202 32 0
          DSP_config_DSP_inst31_inst_bbb/my_dsp 186 47 0
          DSP_config_DSP_inst31_inst_bbbb/my_dsp 63 197 0

   -NOTE 3: To place cascade shape instance, you only need to specify the location of its "reference component".
            Please see the explanation and example provided in section "7, "design.cascade_shape_instances" below.

   -NOTE 4: You can compute the number of macros in the netlist using the following bash script:

      #!/bin/bash
      #Begin
      egrep "DSP|BRAM|URAM" design.nodes > tmp1
      nBasicMacros=`wc -l < tmp1`
      echo "hi $nBasicMacros"

      egrep "Begin"  design.cascade_shape_instances > tmp2
      nShapes=`wc -l < tmp2`

      nShapes=`egrep "Begin"  design.cascade_shape_instances | wc -l`
      echo "nSahpes $nShapes"

      nMacros=`egrep "inst"  design.cascade_shape_instances | wc -l`

      nMacros=`expr $nBasicMacros - $nMacros + $nShapes`
      echo "nNacros: $nMacros" 
      #end

**6. sample.pl**
   Sample macro placement specification file.

**7. design.cascade_shape**
     - Contains a list of cascaded macro shapes that are assembled by cascading basic macro types 
       (ie. BRAMs, DSPs and URAMs).
     - IMPORTANT NOTE:  Cascaded macro shapes can only be placed on columns of their respective types 
       as prescribed in the design.scl file.
     - For example:  The BRAM_CASCADE_5 macro is built by cascading single column of 5 RAMB36E2 BRAM 
       types and can be placed on BRAM colunms sites only:

          Shape BRAM_CASCADE_5 5 1
          BEGIN
               RAMB36E2
               RAMB36E2
               RAMB36E2
               RAMB36E2
               RAMB36E2
          End
     
      - Shapes can also straddle multiple columns, for instance URAM_CASCADE_8x2 is an 8x2 array occupying 2 URAM columns and
        can be placed on URAM column sites only:

           Shape URAM_CASCADE_8x2 8 2
           BEGIN
                URAM288 URAM288
                URAM288 URAM288
                URAM288 URAM288
                URAM288 URAM288
                URAM288 URAM288
                URAM288 URAM288
                URAM288 URAM288
                URAM288 URAM288
           End
   
       -  The complete list of macro shape types is listed below:
             Shape BRAM_CASCADE_2 2 1
             Shape BRAM_CASCADE_5 5 1
             Shape BRAM_CASCADE_7 7 1
             Shape BRAM_CASCADE_10 10 1
             Shape BRAM_CASCADE_30 30 1
             Shape DSP_CASCADE_2 2 1
             Shape DSP_CASCADE_5 5 1
             Shape DSP_CASCADE_7 7 1
             Shape DSP_CASCADE_10 10 1
             Shape DSP_CASCADE_60 60 1
             Shape URAM_CASCADE_8x2 8 2
  
**8. design.cascade_shape_instances** 
      - This file lists the cascaded macro shape instances
      - For example,

        BRAM_cascade_10 10 1 BRAM_CASCADE_10_inst_b
        BEGIN
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst          <---- Reference Component
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst10
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst2
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst3
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst4
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst5
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst6
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst7
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst8
             BRAM_CASCADE_10_inst_b/RAMB36E2_inst9
        END

        In this example, the  BRAM_CASCADE_10_inst_b can only be placed on BRAM column sites starting BRAM_CASCADE_10_inst_b/RAMB36E2_inst 
               and ending with BRAM_CASCADE_10_inst_b/RAMB36E2_inst10

      - NOTE 1: Each cascade instance has a reference component.  In order to place a cascade shape, it is sufficient to only specify the location of its reference component.  
                All the other components will be placed accordingly. For example, to place BRAM_CASCADE_10_inst_b, you only need to specify the location of its reference component 
                in design.pl as follows:

             BRAM_CASCADE_10_inst_b/RAMB36E2_inst 100 0 0

             This automatically places the components BRAM_CASCADE_10_inst_b/RAMB36E2_inst2 to BRAM_CASCADE_10_inst_b/RAMB36E2_inst10 in their respective
             locations, i.e. locations (100 5 0) ... (100 45 0). 

      - NOTE 2: The following specifies a recipe for determining the reference components for BRAM, URAM, and DSP cascade instances:

        BRAM cascade reference component: The reference component for a BRAM cascade ends with the suffix "_inst". For instance, in the example 
        above, the reference component is "BRAM_CASCADE_10_inst_b/RAMB36E2_inst"

        URAM cascade reference component: The reference component for a URAM cascade ends with the suffix "_inst1". For instance,
        the reference component for the URAM cascade instance below is "URAM_CASCADE_8x2_inst_b/URAM288_inst1"

            URAM_cascade_8x2 8 2 URAM_CASCADE_8x2_inst_b
            BEGIN
                URAM_CASCADE_8x2_inst_b/URAM288_inst1      <---- Reference Component
                URAM_CASCADE_8x2_inst_b/URAM288_inst2
                URAM_CASCADE_8x2_inst_b/URAM288_inst3
                URAM_CASCADE_8x2_inst_b/URAM288_inst4
                URAM_CASCADE_8x2_inst_b/URAM288_inst5
                URAM_CASCADE_8x2_inst_b/URAM288_inst6
                URAM_CASCADE_8x2_inst_b/URAM288_inst7
                URAM_CASCADE_8x2_inst_b/URAM288_inst8
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst10
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst11
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst12
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst13
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst14
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst15
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst16
                URAM_CASCADE_8x2_inst_b/URAM_cascade_sub_instance/URAM288_inst9
            END

      DSP cascade reference component: The reference component for a DSP cascade conains the following two strings in the instance name: "_instance_name1" and "i_primitive"
      For instance, the reference instance for the DSP cascade below is "DSP_CASCADE_2_inst_b/your_instance_name1/U0/i_synth/i_synth_option.i_synth_model/opt_8series.i_uniwrap/i_primitive"

           DSP_cascade_2 2 1 DSP_CASCADE_2_inst_b
           BEGIN
                DSP_CASCADE_2_inst_b/your_instance_name1/U0/i_synth/i_synth_option.i_synth_model/opt_8series.i_uniwrap/i_primitive
                DSP_CASCADE_2_inst_b/your_instance_name2/U0/i_synth/i_synth_option.i_synth_model/opt_8series.i_uniwrap/i_primitive
           END

            
**9. design.regions**
      -  This file lists prescription for region constraints for placeable instances that have region constraints
      -  All region constraints boxes are exclusive, i.e., xLo <= x < xHi and yLo <= y < yHi
      -  Placeable instances not showing in the InstanceToRegionCosntraintMapping session are not subject to any region constraint
      -  The format is as follows: 

          RegionConstraint BEGIN <region constraint ID> <num of boxes in this region constraint>
          box <xLo> <yLo> <xHi> <yHi>
            ......
          RegionConstraint END

          InstanceToRegionConstraintMapping BEGIN
            <instance name> <region constraint ID>
            ......
          InstanceToRegionConstraintMapping END

       - For example, the following defines two regions with 1 box each and their respective member instances:

           #Region definitions
           RegionConstraint BEGIN 0 1
             rect 0 0 211 120
           RegionConstraint END

           RegionConstraint BEGIN 1 1
             rect 0 120 211 300
           RegionConstraint END

           #Region instance members
           InstanceToRegionConstraintMapping BEGIN
             BRAM_config_BRAM_SDP_inst762_inst_b/my_sdpram 0
             BRAM_config_BRAM_SDP_inst762_inst_bb/my_sdpram 1
             BRAM_config_BRAM_SDP_inst762_inst_be/my_sdpram 1
             BRAM_config_BRAM_SDP_inst762_inst_bf/my_sdpram 1
             BRAM_config_BRAM_SDP_inst762_inst_bh/my_sdpram 0
             BRAM_config_BRAM_SDP_inst762_inst_bl/my_sdpram 0
             BRAM_config_BRAM_SDP_inst762_inst_bm/my_sdpram 0
           InstanceToRegionConstraintMapping END

**10. design.dcp**
        This file contains the synthesized netlist checkpoint that is required as an input by the Vivado executable.
