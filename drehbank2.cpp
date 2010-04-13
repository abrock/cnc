#include <iostream>

#include <cmath>

using namespace std;

/**
 * Gets the point where to start the lines.
 *
 * \param haystack Array of points.
 * \param length Length of the array of points.
 * \param x maximum x value.
 * \param y maximum y value.
 * \return void 
 */
void startpoint(double haystack[][2], int length, double &x, double &y) {
 x = haystack[0][0];
 y = haystack[0][1];
 for (int i = 1; i < length; i++) {
  if (haystack[i][0] > x) {
   x = haystack[i][0];
  }
  if (haystack[i][1] > y) {
   y = haystack[i][1];
  }
 }
}

void drawpolygon(double haystack[][2], int length) {
 double factor(10);
 cout << "<path d=\" M 0,0 ";
 for (int i = 0; i < length; i++) {
  cout << " L " << haystack[i][0]*factor << "," << haystack[i][1]*factor << endl;
 }
 cout << "Z \" style=\"fill: none; stroke: black; stroke-width: 2px\" />";
}

void drawlines(double haystack[][3], int length) {
 double factor(10);
 cout << "<path d=\" M 0,0 ";
 for (int i = 0; i < length; i++) {
  cout << " M " << haystack[i][0]*factor << "," << haystack[i][2]*factor
	 << " L " << haystack[i][0]*factor << "," << haystack[i][2]*factor << endl;
 }
 cout << "Z \" style=\"fill: none; stroke: black; stroke-width: 2px\" />";
}

/**
 * Searches for intersections between a chain of lines and a single line which is parallel to the x-achsis
 */
void lineMatches(double haystack[][2], double upmatches[][2], double downmatches[][2], int length, double position, double ap, int &upmatchcounter, int &downmatchcounter) {
 upmatchcounter = 0;
 downmatchcounter = 0;
 double dx;
 double dy;
 for (int i = 0; i < length - 1; i++) {
  // Check if the horizontal line intersects the beginning of the shape
  if (haystack[i][1] <= position && haystack[i + 1][1] >= position) {
   dy = haystack[i + 1][1] - haystack[i][1];
   if (dy == 0.0) {
    continue;
   }
   dx = haystack[i + 1][0] - haystack[i][0];
   upmatches[upmatchcounter][0] = haystack[i][0] + dx * (ap / dy);
   upmatches[upmatchcounter][1] = position;
   upmatchcounter++;
  }
  // Check if the horizontal line intersects the beginning of the shape
	if (haystack[i][1] >= position && haystack[i + 1][1] <= position) {
   dy = haystack[i + 1][1] - haystack[i][1];
   if (dy == 0.0) {
    continue;
   }
   dx = haystack[i + 1][0] - haystack[i][0];
   downmatches[downmatchcounter][0] = haystack[i][0] + dx * (ap / dy);
   downmatches[downmatchcounter][1] = position;
   downmatchcounter++;
  }
 }
 
}

/**
 * Calculates the lines which shall be machined
 */
void lines(double start[][2], int startlength, double part[][2], int partlength) {
 double ap(1);
 
 int length = startlength;
 if (length < partlength) {
  length = partlength;
 }
 length--;
 
 drawpolygon(start, startlength);
 drawpolygon(part, partlength);
 
 double lines[length][3];
 double startupmatches[length][2];
 double startdownmatches[length][2];
 double partupmatches[length][2];
 double partdownmatches[length][2];
 
 int startupmatchcounter;
 int startdownmatchcounter;
 int partupmatchcounter;
 int partdownmatchcounter;
 
 // distance from nullpoint of y-achsis
 double position(0);
 
 // Number of the line which is beeing processed
 int line(0);
 while (false) {
  position = line*ap;

  lineMatches(start, startupmatches, downmatches, startlength, position, ap, startupmatchcounter, startdownmatchcounter);

  line++;
 }
 
}

int main(void) {
 // pre-product which is a simple cylinder
 double start[4][2];

 start[0][0] = 0;
 start[0][1] = 0;

 start[1][0] = 0;
 start[1][1] = 5;

 start[2][0] = 5;
 start[2][1] = 5;

 start[3][0] = 5;
 start[3][1] = 0;

 // workpiece (a cone)
 double part[3][2];

 part[0][0] = 0;
 part[0][1] = 0;

 part[1][0] = 0;
 part[1][1] = 4;

 part[2][0] = 4;
 part[2][1] = 0;

 lines(start, 4, part, 3);
}
