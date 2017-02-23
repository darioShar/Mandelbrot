#include <SDL\SDL.h>
#include "Plane.h"
#include <iostream>

	using namespace std;


	int main(int arc, char** argv) {
		Vue view(ASPECT_RATIO);

		// Pretty part in my taste (well, more or less...)
	   /*
	   view.xmin = -1.3930840090652123;
	   view.xmax = -1.3929855686636550;
	   view.ymin = -0.0057740940020837;
	   view.ymax = -0.0057187212762075;
	   */

	   // Middle of the biggest black thing, maximum calculations (every point is in the mandelbrot set).
	   
	   view.xmin = -0.5156385696821414;
	   view.xmax = 0.2209879584352034;
	   view.ymin = -0.2071762110330033;
	   view.ymax = 0.2071762110330033;
	   

		Plane Mandelbrot(view);
		Mandelbrot.run();

		return 0;
	}
