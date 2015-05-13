// size of RFduino 15, 15, 3.5
// size of coin d=20.5, h=3.2

module triPiramida(height, width, length) {
    polyhedron(
      points=[ [length/2,width/2,0],[length/2,-width/2,0],[-length/2,-width/2,0],[-length/2,width/2,0], // the four points at base
               [-length/2,0,height],[length/2,0,height]   ],                                 // the apex point 
      faces=[ [0,1,5],  [1,2,4], [2,3,4], [3,0,4], [0,5,4], [1,4,5],             // each triangle side
                  [1,0,3],[2,1,3] ]                         // two triangles for square base
     );
}

module main() {
    
    intersection() {
        
        difference() {
            // main
           translate([-4,-5,-2]) color([79/255, 166/255, 253/255, 1]) cube([24, 26, 12]);
            
            // board space
            translate([1.5,0.5,0]) color([79/255, 166/255, 253/255, 1]) cube([15, 15, 3.6]);
            
            // take board
            translate([-1,5.5,-1]) color([79/255, 166/255, 253/255, 1]) cube([6, 5, 5]);
            
            // battery space
            translate([8,8,3.58]) cylinder(5.3, d=20.5, $fn=360);
            
            // lid space h = 1.321
            translate([8,8,7.6]) cylinder(1.32, d=22, $fn=360);
         
            // connection for lid
            translate([8,8,6.3]) rotate_extrude(convexity = 1, $fn = 100) translate([10.5, 0, 0]) circle(r = 0.5, $fn = 100);
            
            
            // holes for holders
            translate([8,-2,1.69]) triPiramida(1.5, 3, 24);
            translate([-4, -3.5, 0]) color([79/255, 166/255, 253/255, 1]) cube([24, 3, 1.7]);
            
            translate([8,18,1.69]) triPiramida(1.5, 3, 24);
            translate([-4, 16.5, 0]) color([79/255, 166/255, 253/255, 1]) cube([24, 3, 1.7]);

        }
        
        translate([8,8,-2.1]) color([79/255, 166/255, 253/255, 1]) resize([25,29,11]) cylinder(10, d=26, $fn=360);
    }
    
//        translate([1,18.9,-2]) color([79/255, 166/255, 253/255, 1]) cube([14, 6, 6.0]);
}


translate([0,-2, 2]) main();





