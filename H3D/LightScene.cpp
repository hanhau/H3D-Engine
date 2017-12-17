#include "Light.hpp"
#include "FileSystem.hpp"

namespace h3d {
	Lightscene::Lightscene(h3d::AllocationSource as) {
	
	}
	Lightscene::~Lightscene(){
	
	}

	// File Loading/Saving
	void Lightscene::saveToFile(char Path[]) {
		h3d::FileHandle fh;
		fh.open(Path);



		fh.close();
	}

	void Lightscene::loadFromFile(char Path[]) {
		h3d::FileHandle fh;
		fh.open(Path);

		fh.close();
	}

	// Adding Lights
	int64_t Lightscene::addLight(h3d::Light light) {
		return 0;
	}
}