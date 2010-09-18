
template<class T>
class Bezier {
	static point<T> calculate(T param, vector<point<T> >& points, unsigned int limit) {
		if (points.size() < 2 || limit < 2 || param < 0.0 || param > 1.0) {
			return point<T>(0.0, 0.0);
		}
		
		if (limit == 2) {
			return (1-param) * points[0] + param * points[1];
		}
		return (1-param) * points[0] + param * points[1];
	}
	
	static unsigned int n_over_k(unsigned int n, unsigned int k) {
		if (2 * k > n) {
			return n_over_k(n, n-k);
		}
		if (k == 0) {
			return 1;
		}
		unsigned int result = 1;
		for (unsigned int i = n; i >= (n-k); i--) {
			result *= i;
		}
		for (unsigned int i = 2; i <= k; i++) {
			result /= i;
		}
		return result;
	}
};

