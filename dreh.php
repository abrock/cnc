<?php

$t = new dreh;

$t->start = array(
 array(0,0),
 array(0,4),
 array(4,4),
 array(4,0)
);

$t->part = array(
 array(0,0),
 array(0,4),
 array(4,0)
);

$t->open_draw_file('draw1.svg');

$t->drawline($t->start);
$t->drawline($t->part);

$t->getMaxStart();

$t->drawdots(array($t->maxstart));
$t->drawdots(array($t->minstart));

$t->getLines();

$t->shutdown();

class dreh {
 var $depth = 1;
 var $part, $start;
 var $out;
 var $scale = 50;
 var $circleradius = 0.1;
 var $linedepth = 1;
 
 /**
  * Draws a bunch of dots.
  *
  * @param array array of 2D-points.
  */
 function drawdots($a) {
  if ($this->fp === false) {
   return;
  }
  foreach ($a as $dot) {
   fputs($this->fp, '<circle cx="'.($this->scale*$dot[0]).'" cy="'.($this->scale*$dot[1]).'" r="'.($this->scale*$this->circleradius).'" />'."\r\n");
  }
 }
 
 function getLines() {
  for ($depth = $this->maxstart[1]; $depth >= $this->minstart[1]; $depth -= $this->linedepth) {
   $this->getIntersections($this->part, $depth);
  }
 }
 
 /**
  * Gets the intersections between
  */
 function getIntersections($a, $d) {
 
 }

 /**
  * Draws a line.
  *
  * @param array array of 2D-points.
  */
 function drawline($a) {
  if ($this->fp === false) {
   return;
  }
  fputs($this->fp, '<path d="');
  $first = true;
  foreach ($a as $dot) {
   if ($first) {
    fputs($this->fp, 'M ');
    $first = false;
   }
   else {
    fputs($this->fp, 'L ');
   }
   fputs($this->fp, ($this->scale*$dot[0]).' '.($this->scale*$dot[1])."\r\n");
  }
  fputs($this->fp, 'z" />');
 }
 
 /**
  * Gets the maximum dimensions (x and y) of the raw shape.
  */
 function getMaxStart() {
  $this->maxstart = array($this->start[0][0], $this->start[0][1]);
  $this->minstart = array($this->start[0][0], $this->start[0][1]);
  foreach ($this->start as $d) {
   $this->maxstart[0] = max($this->maxstart[0], $d[0]);
   $this->maxstart[1] = max($this->maxstart[1], $d[1]);

   $this->minstart[0] = min($this->minstart[0], $d[0]);
   $this->minstart[1] = min($this->minstart[1], $d[1]);
  }
 }
 
 function open_draw_file($name) {
  $this->fp = fopen($name, 'w');
  if ($this->fp === false) {
   return;
  }
  fputs($this->fp, '<?xml version="1.0" encoding="UTF-8"?>
<svg xmlns="http://www.w3.org/2000/svg"
	xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns:ev="http://www.w3.org/2001/xml-events"
	version="1.1" baseProfile="full"
	width="700px" height="400px" viewBox="0 -10 500 500">
	<style type="text/css">
<![CDATA[
* {stroke-width: 2px; stroke: black; fill: none}
]]>
</style>');
 }
 
 function shutdown() {
  if ($this->fp !== false) {
   fputs($this->fp, '</svg>');
   fclose($this->fp);
  }
 }
}

?>