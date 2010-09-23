/*!
	Calculate binomial coefficients
*/
unsigned int n_over_k(unsigned int n, unsigned int k) {
	if (k == 0 || k == n || n == 0) {
		return 1;
	}
	if (k == 1 || k == n-1) {
		return n;
	}
	
	return n_over_k(n-1, k) + n_over_k(n-1, k-1);
}

/*!
	Calculate x^b where x is a real number and b a natural number.
	
	
*/
template<class T>
T bin_exp(T x, unsigned int b) {
	T result = (T)1;
	for (int i = sizeof(b)*8-1; i >= 0; i--) {
		result *= result;
		if (b & 1<<i) {
			result *= x;
		}
	}
	return result;
}