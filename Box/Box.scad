height = 40;
width = 40;
length = 60;
thick = 1.2;
$fn = 20;

module base()
{
    difference()
    {
        cube([length + 2*thick, width + 2*thick, height + thick], center = true);
        
        translate([0, 0, thick * 0.51])
        cube([length, width, height], center = true);
        
        translate([length/2, 0, height/2])
        cube([5, width, 2], center = true);
    }
    
    translate([-length/2 + 4, width/2 -4, height/2])
    cube([8, 8, thick], center = true);

    translate([-length/2 + 4, -width/2 +4, height/2])
    cube([8, 8, thick], center = true);

    translate([0, 8.2, 12])
    difference()
    {   
        cube([23 + 2*thick, 23 + thick, 15 + thick], center = true);
        
        translate([0, -thick * 0.51, thick * 0.51])
        {
            cube([23, 23, 15], center = true);
            
            translate([23/2, 23/2 - 3/2 - 16, thick * 0.51])
            cube([5, 3, 15], center = true);
            
            translate([-23/2, 23/2 - 3/2 - 16, thick * 0.51])
            cube([5, 3, 15], center = true);
            
            /*
            translate([0, 23/2 - 5/2 - 27, 0])
            #cube([10, 5, 10], center = true);
            
            translate([-8, 23/2 - 5/2 - 27, 0])
            #cube([8, 5, 10], center = true);
            */
        }
    }
}

module mobile()
{
    translate([length / 4, 0, height / 2 + thick])
    {
        cube([length / 2 + 2*thick, width + 2*thick, thick], center = true);
        
        translate([length / 4 - 7, (width + thick)/ 2 - thick - 0.2, -4])
        cube([8, thick, 8], center = true);
        
        translate([length / 4 - 7, -(width + thick)/ 2 +thick + 0.2, -4])
        cube([8, thick, 8], center = true);
    }
}

module top()
{
    translate([- length / 4, 0, height / 2 + thick])
    cube([length / 2 + 2*thick, width + 2*thick, thick], center = true);
} 

module upperScrews()
{
    translate([-length/2 + 4, width/2 -4, height/2])
    cylinder(d = 3, h = 5, center = true);
    
    translate([-length/2 + 4, -width/2 +4, height/2])
    cylinder(d = 3, h = 5, center = true);
}

module sideScrews()
{
    translate([length/2 -7,  0, height/2 - 3])
    rotate([90, 0, 0])
    cylinder(d = 4, h = width * 1.2, center = true);
}

module Base()
{
    difference()
    {
        base();
        upperScrews();
        sideScrews();
    }
}

module Mobile()
{
    difference()
    {
        mobile();
        sideScrews();
    }
}

module Top()
{
    difference()
    {
        top();
        upperScrews();
        translate([-9, -10.5, height/2])
        cylinder(d = 5.2, h = 5, center = true); 
    }
}

//Base();
//Mobile();
Top();