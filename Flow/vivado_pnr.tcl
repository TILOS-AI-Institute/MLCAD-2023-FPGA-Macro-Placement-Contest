set dcp_path "design.dcp"
set io_tcl_path "place_io.tcl"
set macro_tcl_path "place_macro.tcl"
set placed_checkpoint_path "vivado.placed.dcp"
set routed_checkpoint_path "vivado.routed.dcp"

puts "Opening Unrouted Checkpoint..."
open_checkpoint $dcp_path

set_param place.timingDriven false

puts "Placing IOs..."
source $io_tcl_path

puts "Placing DSPs and BRAMs..."
source $macro_tcl_path

puts "Placing Design..."
place_design -verbose

# puts "Writing Placed Checkpoints..."
# write_checkpoint -force $placed_checkpoint_path

puts "Routing Design..."
route_design -no_timing_driven -verbose

# puts "Writing Routed Checkpoints..."
# write_checkpoint -force $routed_checkpoint_path

puts "Report Congestiong Level..."
report_design_analysis -congestion -min_congestion_level 3

puts "Reporting Routing Status..."
report_route_status
