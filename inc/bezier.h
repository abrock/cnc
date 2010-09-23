
template<class T>
class bezier {
	public:
	
	static point<T> calculate(T param, vector<point<T> >& points) {
		point<T> result;
		
		unsigned int n = points.size() - 1;
		
		for (unsigned int i = 0; i <= n; i++) {
			result += points[i] * (bin_exp(1 - param, n - i) * n_over_k(n, i) * bin_exp(param, i));
			//cout << points[i] << " * " << 1 - param << "^" << n - i << " * " << param << "^" << i << " * " << n << "/" << i << endl; 
		}
		//cout << result << endl << endl;
		
		return result;
	}
};

