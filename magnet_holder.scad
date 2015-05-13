include <threads.scad>

module bolt() {
    translate([0,0,-5]) color([1, 1, 0, 1]) cylinder(5.05, d=10, $fn=360);
    metric_thread(8, 1, 3);
}

module holder() {
    difference() {
        // diameter, pitch, length
        bolt();
        
        // magnet place
        translate([0,0,-4]) color([1, 1, 0, 1]) cylinder(7.1, d=5.2, $fn=360);
        
        // for spoke thread 
        translate([-5.5,-1,-2]) cube([11, 2, 6]);
    }
    
    x = 3.4;
    y = 3.4;
    for(i = [0 : 1 : 15]) {
        a = i*(360/15.0);
        translate([x*cos(a)-y*sin(a),x*sin(a)+y*cos(a),-5]) rotate(a+45) cube([0.4,0.5,2]);
    }
}

translate([0,0,5])  holder();
