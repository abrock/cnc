#include <iostream>
#include <fstream>
#include <sstream>
#include <list>
#include <vector>
#include <cstdlib>

using namespace std;

template<class T>
class point {
	public:
	
	point() {
		z = 0.0;
		x = 0.0;
	}
	
	/*!
		\brief set the coordinates of the point
		
		\param x T x
		\param z T z
	*/
	void set(T z, T x) {
		(*this).z = z;
		(*this).x = x;
	}
	
	/*!
		\brief Copy an existing point
		
		\param newPoint 
	*/
	void set(point<T>& newPoint) {
		z = newPoint.z;
		x = newPoint.x;
	}
	
	/*!
		\brief Set the coordinates to the maximum of the current coordinates and the coordinates of the given point
		
		\param comp Point to compare with
	*/
	void setMax(point<T>& comp) {
		z = max(z, comp.z + 0.1);
		x = max(x, comp.x + 0.1);
	}
	
	/*!
		\brief Set the coordinates to the minimum of the current coordinates and the coordinates of the given point
		
		\param comp Point to compare with
	*/
	void setMin(point<T>& comp) {
		z = min(z, comp.z - 0.1);
		x = min(x, comp.x - 0.1);
	}
	
	T x;
	T z;
};

template<class T>
point<T> operator + (point<T>& one, point<T>& two) {
	return point<T>(one.z + two.z, one.x + two.x);
}

template<class T>
point<T> operator - (point<T> one, point<T> two) {
	return point<T>(one.z - two.z, one.x - two.x);
}

template<class T>
point<T> operator * (T scalar, point<T>& mul) {
	return point<T>(mul.z * scalar, mul.x * scalar);
}

template<class T>
class line {
	public:
	
	line() {
	}
	
	/*!
		\brief Set beginning and end of the line
		
		\param start Beginning of the line
		\param stop End of the line
	*/
	void set(point<T> start, point<T> stop) {
		(*this).start.set(start);
		(*this).stop.set(stop);
	}
	
	/*!
		Get a point on the line
		
		\param scalar location of the point, e.g. 0 for startpoint
		or 0.5 for point in the middle between start and end.
	*/
	point<T> param(T scalar) {
		return point<T>(start + (stop-start)*scalar);
	}
	
	bool intersection(line<T>& comp, T& position) {
		
		// Construct the left side of a linear equation
		point<T>one(stop - start);
		point<T>two(comp.start - comp.stop);
		
		// Construct the right side
		point<T>right(comp.start - start);
		
		return false;
	}
	
	// Beginning and end of the line
	point<T> start, stop;
};

template<class T>
inline ostream& operator<< (ostream& out, const point<T>& p) {
	return out << p.z << " " << p.x;
}


template<class T>
class lathe {
	public:

	lathe() {

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
						<< "plot 'source.data' title 'Source' with lines, 'dest.data' title 'Destination' with lines;\"";
		system(command.str().c_str());
		//cout << command.str();
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
};

int main(void) {

	lathe<double> test;

	test.addPoint(true, 0.0, 0.0);
	test.addPoint(true, 0.0, 1.0);
	test.addPoint(true, 1.0, 0.0);
	test.addPoint(false, 0.0, 0.0);
	test.addPoint(false, 0.0, 1.0);
	test.addPoint(false, 1.0, 1.0);
	test.addPoint(false, 1.0, 0.0);

	

	test.invokeGnuplot();

	return 0;
}
