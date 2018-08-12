#include "../../H3D/Graphics/Light.hpp"
#include "../../H3D/System/FileSystem.hpp"

namespace h3d {
	Lightscene::Lightscene(h3d::AllocationSource as) {
	
	}
	Lightscene::~Lightscene(){
	
	}

	// File Loading/Saving
	void Lightscene::saveToFile(const char Path[]) {
		h3d::FileHandle fh;
		fh.open(Path);



		fh.close();
	}

	void Lightscene::loadFromFile(const char Path[]) {
		h3d::FileHandle fh;
		fh.open(Path);

		fh.close();
	}

	// Adding Lights
	int64_t Lightscene::addLight(h3d::Light light) {
		return 0;
	}
}