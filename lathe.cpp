#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

template<class T>
class line;

#include "point.h"

#include "hit.h"

#include "line.h"


template<class T>
bool inIntervall(T value, T start, T stop) {
	return (value >= start && value <= stop) || (value <= start && value >= stop);
}

template<class T>
bool inIntervallConst(T value, T start, T stop) {
	return (value >= start && value <= stop);
}

template<class T>
string stringify(T x) {
	ostringstream o;
	if (!(o << x)) {
		return "";
	}
	return o.str();
}

void open(fstream& file, const string filename, bool out) {
	file.open(filename.c_str(), out ? fstream::out : fstream::in);
}



template<class T>
class lathe {
	public:

	lathe() {
		step = 0.05;
		linesIndex = 0;
	}

	void run() {
		clock_t start = clock();
	
		intersections();

		cout << "intersections() took " << 1000.0 * (clock() - start) / (double)(CLOCKS_PER_SEC) << "ms" << endl;
		start = clock();

		gCode();

		cout << "gCode() took " << 1000.0 * (clock() - start) / (double)(CLOCKS_PER_SEC) << "ms" << endl;
		start = clock();

		invokeGnuplot();
		cout << "invokeGnuplot() took " << 1000.0 * (clock() - start) / (double)(CLOCKS_PER_SEC) << "ms" << endl;
	}
	
	/*!
		Calculate intersections between lines, 
	*/
	void intersections() {
	
		// A list of the hits
		list<hit<T> > hits;
		
		// a 
		line<T> machine;
	
		fstream crosses;
		crosses.open("crosses.data", fstream::out);
		if (!crosses.is_open()) {
			cout << "couldn't open crosses.data" << endl;
			return;
		}
	
		for (double x = maximum.x; x >= minimum.x; x -= step) {
			machine.set(maximum.z, x, minimum.z, x);
			intersections(source, machine, true, hits);
			intersections(dest, machine, false, hits);
			
			//hit<T>::display(crosses, machine, hits);
			
			makelines(machine, hits);
			
			hits.clear();
		}
		crosses.close();
		
		fstream linesFile;
		linesFile.open("lines.data", fstream::out);
		if (!linesFile.is_open()) {
			cout << "couldn't open lines.data" << endl;
			return;
		}
		
		//line<T>::display(linesFile, lines);
		//gnuplotCommand << ", 'lines.data' title 'lines' with lines";
		
		linesFile.close();
	}
	
	/*!
		Generate G-Code
	*/
	void gCode() {
		fstream gCodeData;
		gCodeData.open("gcode.data", fstream::out);
		if (!gCodeData.is_open()) {
			cout << "couldn't open file gcode.data" << endl;
			return;
		}
	
		list<point<T> > maxima;
		
		getLocalMaxima(dest, maxima);
		
		// true when no more lines must be converted into g-code
		bool finished = false;
		
		//
		T lastX = lines.front().start.x + step;
		
		fstream file;
		
		bool finishedLine = false;
		
		fstream gCode;
		gCode.open("gcode.ngc", fstream::out);
		if (!gCode.is_open()) {
			cout << "couldn't open file gcode.ngc" << endl;
			return;
		}
		
		point<T> lastStop((*lines.begin()).stop);
		
		class list<line<T> >::iterator last = lines.begin();
		
		int counter = 0;
		
		bool firstRun = true;
		
		T lastHeight = 0.0;
		T lastZ = 0.0;
		
		while(!finished) {
			if (file.is_open()) {
				file.close();
				linesIndex++;
			}
			
			open(file, "lines_" + stringify(linesIndex) + ".data", true);
			if (!file.is_open()) {
				cout << "couldn't open file lines_" + stringify(linesIndex) + ".data" << endl;
				return;
			}
			gnuplotCommand << ", 'lines_" + stringify(linesIndex) + ".data' title '' with lines";
			cout << ++counter << endl;
			if (counter > 100) {
				break;
			}

			finished = true;
			firstRun = true;
			for (class list<line<T> >::iterator it = lines.begin(); ; it++) {
				if (it == lines.end()) {
					moveTo(gCode, gCodeData, point<T>(lastZ, maximum.x), true);
					break;
				}

				/*
				if (lastX != (*it).start.x) {
					finishedLine = false;
				}
				
				if (lastX != (*it).start.x && (*it).active) {
					file << (*it) << endl;
					gCodeLine(gCode, (*it));
					(*it).active = false;
					finishedLine = true;
				}
				if (!finishedLine && (*it).active) {
					file << (*it) << endl;
					gCodeLine(gCode, (*it));
					(*it).active = false;
					finishedLine = true;
				}
				// */
				/*
				if (firstRun) {
					lastHeight = (*it).start.x;
				}
				// */
				
				if ((sameNut((*it), (*last)) || firstRun) && (*it).active) {
					if (firstRun) {
						moveTo(gCode, gCodeData, point<T>((*it).start.z, maximum.x), true);
					}
					file << (*it) << endl;
					gCodeLine(gCode, gCodeData, (*it));
					(*it).active = false;
					finishedLine = true;
					last = it;
					firstRun = false;
					lastZ = (*it).stop.z;
				}
				//*
				// */
				
				if ((*it).active) {
					finished = false;
				}
				lastX = (*it).start.x;
			}
		}
		file.close();
	}
	
	bool sameNut(line<T> current, line<T> previous) {
		if (!previous.startSource && !current.stopSource && previous.startIndex < current.stopIndex) {
			return false;
		}
		if (current.startSource && current.stopSource) {
			return true;
		}
		if (!previous.stopSource && (current.stopIndex >= previous.stopIndex)) {
			return true;
		}
		if (previous.startSource && previous.stopSource) {
			return true;
		}

		return false;
	}
	
	/*!
		Generate a 
	*/
	void gCodeLine(ostream& ngc, ostream& data, line<T>& myLine) {
		moveTo(ngc, data, myLine.start, true);
		moveTo(ngc, data, myLine.stop, false);
	}
	
	void moveTo(ostream& ngc, ostream& data, point<T> dest, bool g0) {
		data << dest << endl;
		if (g0) {
			ngc << "G0 ";
		}
		else {
			ngc << "G1 ";
		}
		dest.gCodePoint(ngc);
		ngc << endl;
	}
	
	/*!
		Calculate the lines which must be executed by the machine
		
		\param machine line to execute
		\param hits list of hits between the line and the shapes
	*/
	void makelines(line<T>& machine, list<hit<T> >& hits) {
		hits.sort();
		bool inSource = false;
		bool inDest = false;
		bool lineStarted = false;
		point<T> start;
		hit<T> startHit;
		for (class list<hit<T> >::iterator it = hits.begin(); it != hits.end(); it++) {
			if ((*it).source) {
				inSource = !inSource;
			}
			else {
				inDest = !inDest;
			}
			if (inSource && !inDest && !lineStarted) {
				lineStarted = true;
				start = machine.param((*it).param);
				startHit = (*it);
			}
			if ((inDest || !inSource) && lineStarted) {
				lineStarted = false;
				lines.push_back(line<T>(start, machine.param((*it).param), startHit, (*it)));
			}
		}
	}
	
	
	
	/*!
		Calculate the intersections between a shape and a line.
		
		\param shape Shape to calculate intersections with
		\param machine Line the machine will execute
		\param source true if it is a source shape, false for a destination shape
		\param hits List of the hits found.
	*/
	void intersections(vector<point<T> >& shape, line<T>& machine, bool source, list<hit<T> >& hits) {
		T param;
		line<T> shapeLine;
		for (unsigned int i = 1; i < shape.size(); i++) {
			shapeLine.set(shape[i-1], shape[i]);
			if (machine.intersection(shapeLine, param)) {
				hits.push_back(hit<T>(source, param, i));
			}
		}
	}
	
	int countIntersections(vector<point<T> >& shape, line<T>& myLine) {
		list<hit<T> > hits;
		intersections(shape, myLine, true, hits);
		return hits.size();
	}

	/*!
		\brief Add a point to either source or destination
		
		\param destination true if the point is a point of the destination,
						false if it belongs to the source shape.
		\param T z component of the point
		\param T x component of the point
	*/
	void addPoint(bool destination, T z, T x) {
		point<T> newPoint;
		newPoint.z = z;
		newPoint.x = x;
		maximum.setMax(newPoint);
		minimum.setMin(newPoint);
		if (destination) {
			dest.push_back(newPoint);
		}
		else {
			source.push_back(newPoint);
		}
	}

	void gnuplot(const char prefix[]) {
		//todo
	}

	/*!
		\brief write the source and destination shapes into files for visualization using gnuplot
	*/
	void gnuplot() {
		gnuplot(source, "source.data");
		gnuplot(dest, "dest.data");
	}

	/*!
		\brief Write a vector of points into a file for
						visualization using gnuplot.
						
		\param points Vector of points
		\param filename const char[] name of the file to write to.
	*/
	void gnuplot(vector<point<T> >& points, const char filename[]) {
		fstream out;
		out.open(filename, fstream::out);
		if (!out.is_open()) {
			cout << "file " << filename << "couldn't be opened" << endl;
			out.close();
			return;
		}
		gnuplot(out, points);
		out.close();
	}

	/*!
		\brief Call the gnuplot program
		
	*/
	void invokeGnuplot() {
	
		gnuplot();
		gnuplotRaw();
		gnuplotGCode();
	}
	
	void gnuplotRaw() {
		stringstream command;
	
		command	<< "gnuplot -e \"set terminal svg;"
						<< "set output 'plot.svg';"
						<< "set xrange[" << minimum.z << ":" << maximum.z << "];"
						<< "set yrange[" << maximum.x << ":" << minimum.z << "];"
						<< "plot 'source.data' title 'Source' with lines, 'dest.data' title 'Destination' with lines"
						<< gnuplotCommand.str() << ";\" ";
		system(command.str().c_str());
		//cout << command.str();
		
		fstream commandFile;
		
		commandFile.open("gnuplot.sh", fstream::out);
		commandFile << command.str();
		commandFile.close();
	}
	
	void gnuplotGCode() {
		stringstream command;
	
		command	<< "gnuplot -e \"set terminal svg;"
						<< "set output 'gcode.svg';"
						<< "set xrange[" << minimum.z << ":" << maximum.z << "];"
						<< "set yrange[" << maximum.x << ":" << minimum.z << "];"
						<< "plot 'gcode.data' title '' with lines;\" ";
		system(command.str().c_str());
		//cout << command.str();
	}
	
	/*!
		Get the local maxima of a shape.
		
		\param shape Shape
		\param maxima list of the local maxima
	*/
	void getLocalMaxima(vector<point<T> >& shape, list<point<T> > maxima) {
		for (unsigned int i = 1; i < shape.size()-1; i++) {
			if (shape[i-1].x < shape[i].x && shape[i+1].x < shape[i].x) {
				maxima.push_back(shape[i]);
				//cout << shape[i] << endl;
			}
		}
	}

	/*!
		\brief Stuff the contents of a vector of points into a stream
		
		\param out stream to stuff the points into
		\param points vector of points
	*/
	void gnuplot(ostream& out, vector<point<T> >& points) {
		for (class vector<point<T> >::iterator it = points.begin(); it != points.end(); it++) {
			out << (*it) << endl;
		}
	}
	
	
	void testPlot() {
		T start = 0.0;
		T stop = 18.0;
		T step = 0.01;
	
		for (T z = start; z <= stop; z += step) {
			addPoint(true, z, 2.0 + sin(2*z) + sin(0.5*z));
		}
		addPoint(true, stop, 0.0);
	}
	

	private:

	// The shape of the given material
	vector<point<T> > source;

	// The desired shape of the finished part
	vector<point<T> > dest;
	
	// Maximum dimension of source and dest
	point<T> maximum;
	
	// Minimum dimension of source and dest
	point<T> minimum;
	
	// depth of a single step
	T step;
	
	// Lines to execute
	list<line<T> > lines;
	
	// G1-Speed for the lathe
	T g1;
	
	// gnuplot-command
	stringstream gnuplotCommand;
	
	//
	int linesIndex;
	
};

int main(void) {
	time_t start = time(0);
	clock_t startClock = clock();

	lathe<double> test;

	/*
	test.addPoint(true, 0.0, 0.0);
	test.addPoint(true, 0.0, 1.0);
	test.addPoint(true, 1.0, 0.0);
	test.addPoint(false, 0.0, 0.0);
	test.addPoint(false, 0.0, 1.0);
	test.addPoint(false, 1.0, 1.0);
	test.addPoint(false, 1.0, 0.0);
	*/
	
	test.addPoint(false, 0.0, 0.0);
	test.addPoint(false, 0.0, 6.0);
	test.addPoint(false, 18.0, 6.0);
	test.addPoint(false, 18.0, 0.0);

/*	
	test.addPoint(true, 0.0, 0.0);
	test.addPoint(true, 0.0, 1.0);
	test.addPoint(true, 1.0, 1.0);
	test.addPoint(true, 2.0, 1.2);
	test.addPoint(true, 3.0, 1.5);
	test.addPoint(true, 4.0, 2.0);
	test.addPoint(true, 5.0, 2.7);
	test.addPoint(true, 6.0, 3.0);
	test.addPoint(true, 7.0, 0.0);
	test.addPoint(true, 9.0, 5.0);
	test.addPoint(true, 11.0, 0.0);
	*/
	test.testPlot();
	
	test.run();

	cout	<< "Program execution took " << time(0) - start << "s ("
				<< 1000.0 * (clock() - startClock) / (double)(CLOCKS_PER_SEC) << "ms)"
				<< endl;

	return 0;
}
