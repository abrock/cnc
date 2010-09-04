#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

template<class T>
class lathe {
	public:

	lathe() {

	}


	void addPoint(bool destination, T z, T x) {
		vector<T> point;
		point.reserve(2);
		point[0] = z;
		point[1] = x;
		if (destination) {
			dest.push_back(point);
		}
		else {
			source.push_back(point);
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

	void gnuplot(vector<vector<T> >& points, const char filename[]) {
		fstream out;
		out.open(filename, fstream::out);
		gnuplot(points, out);
		out.close();
	}

	void gnuplot(vector<vector<T> >& points, ostream& out) {
		for (class vector<vector<T> >::iterator it = points.begin(); it != points.end(); it++) {
			out << (*it)[0] << " " << (*it)[1] << endl;
		}
	}

	private:

	// The shape of the given material
	vector<vector<T> > source;

	// The desired shape of the finished part
	vector<vector<T> > dest;
};

int main(void) {

	lathe<double> test;

	test.addPoint(true, 0.0, 0.0);
	test.addPoint(true, 0.0, 1.0);
	test.addPoint(true, 1.0, 1.0);
	test.addPoint(false, 0.0, 0.0);
	test.addPoint(false, 0.0, 1.0);
	test.addPoint(false, 1.0, 1.0);
	test.addPoint(false, 1.0, 0.0);

	test.gnuplot();

	return 0;
}
