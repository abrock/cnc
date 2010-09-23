#include "inc/lathe.h"

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
	test.addPoint(false, 0.0, 20.0);
	test.addPoint(false, 80.0, 20.0);
	test.addPoint(false, 80.0, 0.0);

/*	
	test.addPoint(true, 0.0, 0.0);
	test.addPoint(true, 0.0, 7.5);
	test.addPoint(true, 80.0, 20.0);
	test.addPoint(true, 80.0, 0.0);
	//*/
	//test.testPlot();
	test.testBezier();
	
	test.run();

	cout	<< "Program execution took " << time(0) - start << "s ("
				<< 1000.0 * (clock() - startClock) / (double)(CLOCKS_PER_SEC) << "ms)"
				<< endl;

	return 0;
}
