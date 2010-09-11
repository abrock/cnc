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
	point(T z, T x) {
		set(z, x);
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
point<T> operator + (point<T> one, point<T> two) {
	return point<T>(one.z + two.z, one.x + two.x);
}

template<class T>
point<T> operator - (point<T> one, point<T> two) {
	return point<T>(one.z - two.z, one.x - two.x);
}

template<class T>
point<T> operator * (T scalar, point<T> mul) {
	return point<T>(mul.z * scalar, mul.x * scalar);
}

template<class T>
inline ostream& operator<< (ostream& out, const point<T>& p) {
	return out << p.z << " " << p.x;
}

