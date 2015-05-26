include <threads.scad>

// RFduino 15 x 15 x 3.5 mm
// Coin Batttery d=20, h=3.2 mm

difference() {
    cube([23, 39, 10]);
    translate([4, 1.5, 5.1]) cube([15, 15, 5]);
        
    translate([11.5, 28, 5.1]) cylinder(5, d=20, $fn=360);
}
