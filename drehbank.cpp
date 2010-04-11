#include <iostream>
#include <string>
#include <cmath>

using namespace std;


void lines(double start[][2], double part[][2], double tool[][2], double toolholder[][2]) {
 // Depth to cut at once.
 double ap;
 ap = 1;
}

void drawSVG(double lines[][2], iostream file) {

}

void readFile(double haystack[][2], FILE* in) {
 int position = 0;
 while (true) {
  if (!feof(in)) {
   in >> haystack[position][0];
  }
  if (!in.eof()) {
   in >> haystack[position][1];
  }
  else {
   return;
  }
 }
}

int main(void) {
 double start[1][2];
 
 FILE* startfile;
 startfile = fopen("startfile.txt", "r");
 if (startfile == NULL) {
  return 0;
 }
 readFile(start, startfile);
}
