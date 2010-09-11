using namespace std;

template<class T>
class line {
	public:
	
	line() {
	}
	
	line(const point<T>& start, const point<T>& stop) {
		set(start, stop);
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
		point<T>one(stop - start);
		point<T>two(comp.start - comp.stop);
		
		// Construct the right side
		point<T>right(comp.start - start);
		
		// Calculate determinante of the linear equation
		T det = one.z * two.x - two.z * one.x;
		if (det == 0.0) {
			return false;
		}
		
		position = (two.x * right.z - two.z * right.x) / det;
		
		T position2 = (one.z * right.x - one.x * right.z) / det;
		
		if (inIntervall(position, 0.0, 1.0) && inIntervall(position2, 0.0, 1.0)) {
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
};

	/*!
		Display a line using gnuplot
		
		\param out stream to stuff the line into
	*/
template<class T>
inline ostream& operator<< (ostream& out, const line<T>& myLine) {
	return out << myLine.start << endl << myLine.stop << endl;
}

