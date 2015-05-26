include <threads.scad>

module bolt() {
    //translate([0,0,-5]) color([1, 1, 0, 1]) cylinder(5.05, d=10, $fn=360);
    metric_thread(8, 1, 3);
}

module holder_cap() {
    difference() {
        translate([0,0,0.02]) color([1, 1, 0, 1]) cylinder(4.5, d=12, $fn=360);
        
        bolt();
    }
    
    x = 4.05;
    y = 4.05;
    for(i = [0 : 1 : 15]) {
        a = i*(360/15.0);
        translate([x*cos(a)-y*sin(a),x*sin(a)+y*cos(a),2.5]) rotate(a+45) cube([0.5,0.7,2]);
    }
    
}

scale(1.2) translate([0,0,5]) rotate([180,0,0]) holder_cap();
