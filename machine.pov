camera {
 location <450,500,-900>
 look_at <250,0,0>
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
  <0,0,-w/2>,<w,w/4,w/2>
 }
 texture {
  pigment {
   color <0,255,0>
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
   color <255,0,0>
  }
 }
}
#declare xverbindung = box{
 <0,0,-w>, <w,w,xdistance + 3 * w>
 texture {
  pigment {
   color <0,0,255>
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
   color <255,255,255>
  }
 }
}

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
    color <255,255,0>
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
 translate <w,0,0>
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




