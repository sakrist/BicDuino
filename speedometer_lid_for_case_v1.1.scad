// lid
include <threads.scad>

difference() {
    rotate([180,0,0]) metric_thread(22, 1, 3.1);

    translate([0,1,8.5]) rotate([90,0,0]) cylinder(2, d=20);
}
