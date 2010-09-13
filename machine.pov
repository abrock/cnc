#declare w = 45;
#declare h = 90;

#declare xpos = 2*w;
#declare ypos = h+w;
#declare zpos = -300;

#declare x_verfahrweg = 1200;
#declare y_verfahrweg = 900;
#declare z_verfahrweg = 500;

#declare xlaenge = x_verfahrweg + 2 * h + 5*w;

#declare xdistance = y_verfahrweg + h + 7*w;

#declare zlaenge = z_verfahrweg + 2*h + 4*w;

#declare winkelcount = 0;



     
     
camera {
 location <1000,1000,-1000>
 look_at <xlaenge/2,0,250>
}

global_settings {
 ambient_light 0
}

#declare light_amount = 0.5;

light_source {
 <-50,400,-150>, light_amount
}
light_source {
 <-50,400,xdistance+150>, light_amount
}
light_source {
 <xlaenge+50,400,-150>, light_amount
}
light_source {
 <xlaenge+50,400,xdistance+150>, light_amount
} 

light_source {
 <-50,-400,-150>, light_amount
}
light_source {
 <-50,-400,xdistance+150>, light_amount
}
light_source {
 <xlaenge+50,-400,-150>, light_amount
}
light_source {
 <xlaenge+50,-400,xdistance+150>, light_amount
} 

// Gesamtlänge der benötigten Profile 90x45 bzw. 45x45
#declare littlesum = 0;
#declare bigsum = 0;

#declare winkel =
merge {
 box {
  <0,0,-w/2+2>,<w/4,w-2,w/2-2>
 }
 box {
  <w/4,0,-w/2+2>,<w,w/4,w/2-2>
 }
 texture {
  pigment {
   color <0,2,0>
  }
 }
}

#declare xfuehrung = box {
 #declare bigsum = bigsum + (xlaenge)*2;
 #debug concat("B 2 x", str(xlaenge, 5 ,0), "\n")

 <0,0,0>, <xlaenge,h,w>
 texture {
  pigment{
   color <2,0,0>
  }
 }
}
#declare xverbindung = box{
 #declare bigsum = bigsum + (xdistance + 4 * w)*2;
 #debug concat("B 2 x", str((xdistance + 4 * w), 5 ,0), "\n")
 <0,0,-w>, <w,h,xdistance + 3 * w>
 texture {
  pigment {
   color <0,0,2>
  }
 }
}


object {
 xfuehrung
}
object {
 xfuehrung
 translate <0,0,w + xdistance>
}

object {
 xverbindung
 translate <-w,0,0>
}

object {
 xverbindung
 translate <xlaenge,0,0>
}

// Kugellager

#declare bbouter = 11;
#declare bbwidth = 7;
#declare bbinner = 4;

#declare bb = difference {
 cylinder {
  <0,0,0>,<0,0,bbwidth>,bbouter
 }
 cylinder {
  <0,0,-1>,<0,0,bbwidth + 1>,bbinner
 }
 texture {
  pigment {
   color <2,2,2>
  }
 }
}

// Schlitten der X-Achse


#declare xschlitten = union {
 #declare bigsum = bigsum + (w + 2*h)*4;
 #debug concat("B 4 x", str((w + 2*h), 5 ,0), "\n")
 #declare littlesum = littlesum + (w + 2*h)*4;
 #debug concat("L 4 x", str((w + 2*h), 5 ,0), "\n")
 #declare littlesum = littlesum + (3*w)*4;
 #debug concat("L 4 x", str((3*w), 5 ,0), "\n")

 union {
  box {
   <0,-w,-w>,<h,2*h,0>
  }
  box {
   <0,-w,w>,<h,2*h,2*w>
  }
  box {
   <3*w,-w,-w>,<4*w,2*h,0>
  }
  box {
   <3*w,-w,w>,<4*w,2*h,2*w>
  }
  // Untere Verbindung
  box {
   <-w,-w,-w>,<-2,0,2*w>
  }
  box {
   <2*w+2,-w,-w>,<3*w-2,0,2*w>
  }
  texture {
   pigment {
    color <2,2,0>
   }
  }
 }
 union {
  // Obere Lager
  object {
   bb
   translate <w/2, h + bbouter, w - bbwidth>
  }
  object {
   bb
   translate <w/2+w*3, h + bbouter, w - bbwidth>
  }
  object {
   bb
   translate <w/2, h + bbouter, 0>
  }
  object {
   bb
   translate <w/2+w*3, h + bbouter, 0>
  }
  // Untere Lager
  object {
   bb
   translate <w/2, - bbouter, w - bbwidth>
  }
  object {
   bb
   translate <w/2+w*3, - bbouter, w - bbwidth>
  }
  object {
   bb
   translate <w/2, - bbouter, 0>
  }
  object {
   bb
   translate <w/2+w*3, - bbouter, 0>
  }

 }
}

object {
 xschlitten
 translate <xpos,0,0>
}

object {
 xschlitten
 translate <xpos,0,xdistance + w>
}

// Verbindung x-Achse links

#declare set = union {
 object {
  winkel
  rotate <-90,0,0>
  translate <0,w/2,0>
 }    
 
 object {
  winkel
  rotate <-90,0,0>
  translate <0,3*w/2,0>
 }
 
 
 object {
  winkel
  rotate <90,0,0>
  translate <0,w/2,w>
 }  
 
 
 object {
  winkel
  rotate <90,0,0>
  translate <0,3*w/2,w>
 }
 
}

object {
 set
 #declare winkelcount = winkelcount + 4;
}
object {
 set
 #declare winkelcount = winkelcount + 4;
 translate <0,0,xdistance+w>
}

object {
 set
 #declare winkelcount = winkelcount + 4;
 scale <-1,1,1>
 translate <xlaenge,0,0>
}
object {
 set
 #declare winkelcount = winkelcount + 4;
 scale <-1,1,1>
 translate <xlaenge,0,xdistance+w>
}
                                   
// Y-Achse              
              
#declare yfuehrung = union {
 #declare bigsum = bigsum + (xdistance + 4 * w)*2;
 #debug concat("B 2 x", str((xdistance + 4 * w), 5 ,0), "\n")
 box {
  <0,0,0>,<w,h,xdistance + 4 * w>
  translate <-w,h,-w>
 }
 box {
  <0,0,0>,<w,h,xdistance + 4 * w>
  translate <h,h,-w>
 }
 texture {
  pigment {
   color rgb <0,0,2>
  }
 }
}

object {
 yfuehrung
 translate <xpos,0,0>
}



#declare yschlitten = union {
 union { 
  // Oberer Teil
  #declare bigsum = bigsum + (5*w+2*h)*2;
  #debug concat("B 2 x", str((5*w+2*h), 5 ,0), "\n")
  box {
   <0,0,0>,<5*w+2*h,h,-w>
   translate <-2*w,0,0>
  }                   
  box {
   <0,0,0>,<5*w+2*h,h,-w>
   translate <-2*w,0,h+w>
  }                   
  // Unterer Teil
  #declare littlesum = littlesum + (5*w+2*h)*2;
  #debug concat("L 2 x", str((5*w+2*h), 5 ,0), "\n")
  box {
   <0,0,0>,<5*w+2*h,-w,-w>
   translate <-2*w,-h,0>
  }                   
  box {
   <0,0,0>,<5*w+2*h,-w,-w>
   translate <-2*w,-h,h+w>
  }                   
  // Vorderer Abschluss, boxen von oben nach unten
  #declare bigsum = bigsum + (2*w+h);
  #debug concat("B 1 x", str((2*w+h), 5 ,0), "\n")
  #declare littlesum = littlesum + (5*w+2*h)*2;
  #debug concat("L 2 x", str((2*w+h), 5 ,0), "\n")

  box {
   <0,0,0>,<w,w,2*w+h>
   translate <2*w+2*h,h,-w>
  }
  box {
   <0,0,0>,<w,h,2*w+h>
   translate <2*w+2*h,-h,-w>
  }                   
  box {
   <0,0,0>,<w,-w,2*w+h>
   translate <2*w+2*h,-h-w,-w>
  }
  // Mittlerer Abschluss, von oben nach unten
  #declare bigsum = bigsum + (2*w+h);
  #debug concat("B 2 x", str((2*w+h), 5 ,0), "\n")
  box {
   <0,0,0>,<h,w,2*w+h>
   translate <2*w,h,-w>
  }
  box {
   <0,0,0>,<h,w,2*w+h>
   translate <2*w,-2*h,-w>
  }
  // Seitliche Führungen von links nach rechts von vorne nach hinten
  #declare littlesum = littlesum + (2*h+w)*4;
  #debug concat("L 4 x", str((2*h+w), 5 ,0), "\n")
  box {
   <0,0,0><w,2*h+w,w>
   translate <-2*w,-w-h,-2*w>
  }
  box {
   <0,0,0><w,2*h+w,w>
   translate <3*w,-w-h,-2*w>
  }
  box {
   <0,0,0><w,2*h+w,w>
   translate <-2*w,-w-h,h+w>
  }
  box {
   <0,0,0><w,2*h+w,w>
   translate <3*w,-w-h,h+w>
  }
  
  texture {
   pigment {
    color <0,2,2>
   }
  }
 }
 translate <0,2*h,3*w>
}

object {
 yschlitten
 translate <xpos,0,ypos>
}

#declare zachse = union {
 #declare bigsum = bigsum + zlaenge*2;
 #debug concat("B 2 x", str((zlaenge), 5 ,0), "\n")
 union {
  // Lange Führung
  box {
   <0,0,0>,<w,zlaenge,h>
   translate <h+2*w,0,0>
  }
  box {
   <2,0,0>,<w,zlaenge,h>
   translate <h+3*w,0,0>
  }
  texture {
   pigment{
    color <2,0,2>
   }
  }
 }
 translate <0,0,3*w>
}

object {
 zachse
 translate <xpos,zpos,ypos>
}


#debug concat("Winkelcount: ", str(winkelcount,5,0), "\n") 
#debug concat("45x90: ", str(bigsum,5,0), "\n") 
#debug concat("45x45: ", str(littlesum,5,0), "\n") 


