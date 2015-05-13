// lid

difference() {
    union () {
        cylinder(1.32, d=22, $fn=360);
        translate([0,0,1.31]) cylinder(1.58, d=20.5, $fn=360);
        translate([0,0,2.42]) rotate_extrude(convexity = 1, $fn = 100) translate([10, 0, 0]) circle(r = 0.48, $fn = 100);
    }
    
    translate([0,0,1.33]) cylinder(1.6, d=19, $fn=360);
    
    translate([8,-1,1.34]) cube([4,2,3]);
    translate([-12,-1,1.34]) cube([4,2,3]);
    
    translate([-1,8,1.34]) cube([2,4,3]);
    translate([-1,-12,1.34]) cube([2,4,3]);
}