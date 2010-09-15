#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>

using namespace std;

#include "point.h"

double atof(string myString) {
	return atof(myString.c_str());
}

template<class T>
class gCode {
	public:
	
	gCode() {
	
	}
	
	void read(string filename) {
		read(filename.c_str());
	}
	
	void read(const char * filename) {
		fstream gCode;
		gCode.open(filename, fstream::in);
		if (!gCode.is_open()) {
			cout << "couldn't open " << filename << endl;
			return;
		}
		string line;
		//int counter = 0;
		
		T x = 0.0, z = 0.0;
		
		bool stateG0 = false;

		bool firstRun = true;
		
		int g0index = 0, g1index = 0;
		
		g0.reserve(10);
		g1.reserve(10);

		g0.push_back(vector<point<T> >());
		g1.push_back(vector<point<T> >());
		
		
		while (!gCode.eof()) {
			gCode >> line;
			//cout << line << endl;
			if (line[0] == 'g' || line[0] == 'G') {
				if (line[1] == '0') {
					if (firstRun) {
						firstRun = false;
					}
					else {
						g0[g0index].push_back(point<T>(z, x));
						//cout << "g0 " << g0[g0index].back() << endl;
						if (!stateG0) {
							g0index++;
							g0.push_back(vector<point<T> >());
							g1[g1index].push_back(point<T>(z, x));
							//cout << "g1 " << g1[g1index].back() << endl;
						}
					}
					
					stateG0 = true;
				}
				if (line[1] == '1') {
					if (firstRun) {
						firstRun = false;
						
					}
					else {
						g1[g1index].push_back(point<T>(z, x));
						//cout << "g1 " << g1[g1index].back() << endl;
						if (stateG0) {
							g1index++;
							g1.push_back(vector<point<T> >());
							g0[g0index].push_back(point<T>(z, x));
							//cout << "g0 " << g0[g0index].back() << endl;
						}
					}
				
					stateG0 = false;
				}
			}
			if (line[0] == 'z' || line[0] == 'Z') {
				z = atof(line.substr(1));
			}
			if (line[0] == 'x' || line[0] == 'X') {
				x = atof(line.substr(1));
			}
			maximum.setMax(point<T>(z, x));
			minimum.setMin(point<T>(z, x));

			
			line.clear();
		}
		
		gCode.close();
	}
	
	void gnuplot() {
		fstream plot;
		plot.open("g1.data", fstream::out);
		if (!plot.is_open()) {
			cout << "couldn't open g1.data" << endl;
			return;
		}
		gnuplot(plot, g1);
		plot.close();


		plot.open("g0.data", fstream::out);
		if (!plot.is_open()) {
			cout << "couldn't open g0.data" << endl;
			return;
		}
		gnuplot(plot, g0);
		plot.close();
		
		stringstream command;
	
		command	<< "gnuplot -e \"set terminal svg;"
						<< "set output 'gcode.svg';"
						<< "set xrange[" << minimum.z << ":" << maximum.z << "];"
						<< "set yrange[" << maximum.x << ":" << minimum.z << "];"
						<< "plot 'g1.data' title 'G1' with lines, 'g0.data' title 'G0' with lines;\"";
		system(command.str().c_str());
	}
	
	/*!
		Generate code for drawing a bunch of open lines using gnuplot
	*/
	void gnuplot(ostream& out, vector<vector<point<T> > >& lines) {
		for (class vector<vector<point<T> > >::iterator it = lines.begin(); it != lines.end(); it++) {
			gnuplot(out, (*it));
		}
	}
	
	/*!
		Generate code for drawing a bunch of points as an open line using gnuplot.
	*/
	void gnuplot(ostream& out, vector<point<T> >& points) {
		for (class vector<point<T> >::iterator it = points.begin(); it != points.end(); it++) {
			out << (*it) << endl;
		}
		out << endl;
	}
	
	vector<vector<point<T> > > g0;
	vector<vector<point<T> > > g1;
	
	point<T> maximum, minimum;
};

int main(void) {
	gCode<double> gc;
	
	gc.read("gcode.ngc");
	
	gc.gnuplot();

	return 0;
}
