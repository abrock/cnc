using namespace std;

template<class T>
class line {
	public:
	
	line() {
		active = true;
	}
	
	line(const point<T>& start, const point<T>& stop, hit<T>& startHit, hit<T>& stopHit) {
		set(start, stop);
		set(startHit, stopHit);
		active = true;
	}

	line(const point<T>& start, const point<T>& stop) {
		set(start, stop);
		active = true;
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
	
	void set(hit<T> startHit, hit<T> stopHit) {
		(*this).startIndex = startHit.index;
		(*this).stopIndex = stopHit.index;
		(*this).startSource = startHit.source;
		(*this).stopSource = stopHit.source;
	}

	/*!
		\brief Set beginning and end of the line
		
		\param startz z-coordinate of the beginning
		\param startx x-coordinate of the beginning
		\param stopz z-coordinate of the end
		\param stopx x-coordinate of the end
	*/
	void set(T startz, T startx, T stopz, T stopx) {
		(*this).start.set(startz, startx);
		(*this).stop.set(stopz, stopx);
	}
	
	/*!
		Get a point on the line
		
		\param scalar location of the point, e.g. 0 for startpoint
		or 0.5 for point in the middle between start and end.
	*/
	point<T> param(T scalar) {
		return point<T>(start + scalar * (stop-start));
	}
	
	/*!
		Calculate the intersection point of the current line and another one.
		
		\param comp Line to intersect current line with
		\param position variable to store the parameter of the intersection
		\return true if there is an intersection, otherwise false.
	*/
	bool intersection(line<T>& comp, T& position) {
		
		// Construct the left side of a linear equation
		point<T>one(stop);
		one -= start;
		
		point<T>two(comp.start);
		two -= comp.stop;
		
		// Construct the right side
		point<T>right(comp.start);
		right -= start;
		
		// Calculate determinante of the linear equation
		T det = one.z * two.x - two.z * one.x;
		if (det == 0.0) {
			return false;
		}
		
		position = (two.x * right.z - two.z * right.x) / det;
		
		T position2 = (one.z * right.x - one.x * right.z) / det;
		
		if (inIntervallConst(position, 0.0, 1.0) && inIntervallConst(position2, 0.0, 1.0)) {
			return true;
		}
		else {
			return false;
		}
	}
	
	
	/*!
		Display a list of lines using gnuplot
		
		\param out stream to stuff the line into
		\param lines list of lines to display
	*/
	static void display(ostream& out, list<line<T> >& lines) {
		for (class list<line<T> >::iterator it = lines.begin(); it != lines.end(); it++) {
			out << (*it) << endl;
		}
	}
		
	
	// Beginning and end of the line
	point<T> start, stop;
	
	// Indizes of the points of the source/dest shape which correspond to the intersection
	unsigned int startIndex, stopIndex;
	
	// true if start/stop point of the line correspond to points of the source shape
	bool startSource, stopSource;
	
	// Flag for marking the line active
	bool active;
	
	// Avoid constructing and deleting objects by making them member variables:
	//point<T> one, two, right; Bad Idea
};

	/*!
		Display a line using gnuplot
		
		\param out stream to stuff the line into
	*/
template<class T>
inline ostream& operator<< (ostream& out, const line<T>& myLine) {
	return out << myLine.start << endl << myLine.stop << endl;
}

