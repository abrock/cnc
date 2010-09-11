#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <cstdlib>

using namespace std;

#include "point.h"

#include "line.h"

#include "hit.h"

template<class T>
bool inIntervall(T value, T start, T stop) {
	return (value >= start && value <= stop) || (value <= start && value >= stop);
}

template<class T>
class lathe {
	public:

	lathe() {
		step = 0.1;
	}

	void run() {
		intersections();
		
		invokeGnuplot();
		
		gCode();
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
		
		line<T>::display(linesFile, lines);
		
		linesFile.close();
	}
	
	/*!
		Generate G-Code
	*/
	void gCode() {
		list<point<T> > maxima;
		
		getLocalMaxima(dest, maxima);
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
			}
			if ((inDest || !inSource) && lineStarted) {
				lineStarted = false;
				lines.push_back(line<T>(start, machine.param((*it).param)));
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
		for (class vector<point<T> >::iterator it = shape.begin(); it != shape.end(); it++) {
			shapeLine.set(*it, *(it+1));
			if (machine.intersection(shapeLine, param)) {
				hits.push_back(hit<T>(source, param));
			}
		}
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
		stringstream command;
	
		command	<< " gnuplot -e \"set terminal svg;"
						<< "set output 'plot.svg';"
						<< "set xrange[" << minimum.z << ":" << maximum.z << "];"
						<< "set yrange[" << maximum.x << ":" << minimum.z << "];"
						<< "plot 'source.data' title 'Source' with lines, 'dest.data' title 'Destination' with lines, 'crosses.data', 'lines.data' title 'Lines' with lines;\"";
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
				cout << shape[i] << endl;
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
	
	// 
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
	test.addPoint(false, 0.0, 4.0);
	test.addPoint(false, 8.0, 4.0);
	test.addPoint(false, 8.0, 0.0);
	
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
	
	
	test.run();

	cout	<< "Program execution took " << time(0) - start << "s ("
				<< (clock() - startClock) / (double)(CLOCKS_PER_SEC/1000) << "ms)"
				<< endl;

	return 0;
}
