camera {
 location <250,900,250>
 look_at <250,0,250>
}

global_settings {
 ambient_light 0
}

light_source {
 <-50,400,-50>, 0.2
}

light_source {
 <-50,400,-250>, 0.2
}
light_source {
 <500,400,-50>, 0.2
}
light_source {
 <500,400,-250>, 0.2
}

#declare w = 45;

#declare winkel =
merge {
 box {
  <0,0,-w/2>,<w/4,w,w/2>
 }
 box {
  <w/4,0,-w/2>,<w,w/4,w/2>
 }
 texture {
  pigment {
   color <0,2,0>
  }
 }
}

#declare xlaenge = 500;

#declare xdistance = 500;

#declare winkelcount = 0;

#declare xfuehrung =
box {
 <0,0,0>, <xlaenge,w,w>
 texture {
  pigment{
   color <2,0,0>
  }
 }
}
#declare xverbindung = box{
 <0,0,-w>, <w,w,xdistance + 3 * w>
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

// Schlitten der X-Achse

#declare schlittensenkrecht = box {
 <0,-w,-w>,<w,w,0>
}

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

#declare xpos = 2*w;

#declare schlitten =
union {
 union {
  box {
   <0,-w,-w>,<w,2*w,0>
  }
  box {
   <0,-w,w>,<w,2*w,2*w>
  }
  box {
   <3*w,-w,-w>,<4*w,2*w,0>
  }
  box {
   <3*w,-w,w>,<4*w,2*w,2*w>
  }
  texture {
   pigment {
    color <2,2,0>
   }
  }
 }
 union {
  object {
   bb
   translate <w/2, w + bbouter, w - bbwidth>
  }
 }
}

object {
 schlitten
 translate <xpos,0,0>
}

object {
 schlitten
 translate <xpos,0,xdistance + w>
}

// Verbindung x-Achse links
object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <90,0,0>
 translate <0,w/2,w>
}

object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,xdistance + w>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <90,0,0>
 translate <0,w/2,xdistance + 2*w>
}

// Verbindung x-Achse rechts

object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,180>
 translate <xlaenge,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <90,0,180>
 translate <xlaenge,w/2,w>
}

object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,180>
 translate <xlaenge,w/2,xdistance + w>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <90,0,180>
 translate <xlaenge,w/2,xdistance + 2*w>
}

#declare yachse = union {
 box {
  <-w,w,-w>,<0,2*w,xdistance + 3 * w>
 }
 box {
  <2*w,w,-w>,<3*w,2*w,xdistance + 3 * w>
 }
 texture {
  pigment {
   color rgb <0,0,2>
  }
 }
}

object {
 yachse
 translate <xpos,0,0>
}

// Rest


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}


object {
 winkel
 #declare winkelcount = winkelcount + 1;
 rotate <-90,0,0>
 translate <0,w/2,0>
}




