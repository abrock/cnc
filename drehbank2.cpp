#include <iostream>

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
 * Calculates the lines which shall be machined
 */
void lines(double start[][2], int startlength, double part[][2], int partlength) {
 double ap(1);
 
 drawpolygon(start, startlength);
 drawpolygon(part, partlength);
}

int main(void) {
 double start[4][2];

 start[0][0] = 0;
 start[0][1] = 0;

 start[1][0] = 0;
 start[1][1] = 5;

 start[2][0] = 5;
 start[2][1] = 5;

 start[3][0] = 5;
 start[3][1] = 0;

 double part[3][2];

 part[0][0] = 0;
 part[0][1] = 0;

 part[1][0] = 0;
 part[1][1] = 4;

 part[2][0] = 4;
 part[2][1] = 0;

 lines(start, 4, part, 3);
}
