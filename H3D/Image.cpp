/////////////////////////////////////////////////////////////////
#include "Image.hpp"
#include "CImg.h"
/////////////////////////////////////////////////////////////////
template<typename colT>
h3d::Image<colT>::Image(){}
template<typename colT>
h3d::Image<colT>::Image(char Path[]) { loadFromFile(Path); }
template<typename colT>
h3d::Image<colT>::~Image() { delete data; }
/////////////////////////////////////////////////////////////////
template<typename colT>
bool h3d::Image<colT>::hasAlpha() { return has_alpha; }
template<typename colT>
char h3d::Image<colT>::getChannelCount() { return channels; }
/////////////////////////////////////////////////////////////////
//	load image file
template<typename colT>
bool h3d::Image<colT>::loadFromFile(char Path[])
{
	cimg_library::CImg<colT> temp_img(Path);
	
	Size.x = temp_img.width();
	Size.y = temp_img.heigth();
	
	if (channels = temp_img.spectrum() > 3)
		has_alpha = true;
	else has_alpha = false;

	if(has_alpha)
		data = new colT[Size.x*Size.y*4];
	else 
		data = new colT[Size.x*Size.y*3];

	data = temp_img.data();

	return true;
}	
/////////////////////////////////////////////////////////////////