using namespace std;

template<class T>
class hit {
	public:
	
	T param;
	bool source;
	unsigned int index;
	
	hit() {
		source = true;
		param = 0.0;
	}

	/*!
		Set the parameters of the hit
		
		\param true for source, false for destination
		\param param Parameter of the hit.
	*/
	hit(bool source, T param, unsigned int index) {
		set(source, param, index);
	}

	
	/*!
		Set the parameters of the hit
		
		\param true for source, false for destination
		\param param Parameter of the hit.
	*/
	void set(bool source, T param, unsigned int index) {
		(*this).source = source;
		(*this).param = param;
		(*this).index = index;
	}
	
	void display(ostream& out, line<T>& machine) {
		out << machine.param(param) << endl;
	}
	
	static void display(ostream& out, line<T>& machine, list<hit<T> > hits) {
		for (class list<hit<T> >::iterator it = hits.begin(); it != hits.end(); it++) {
			(*it).display(out, machine);
		}
	}
bool operator<(hit<T>& comp) {
	return param < comp.param;
}


};


