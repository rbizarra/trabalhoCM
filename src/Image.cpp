#include "Image.h"

Image::Image(unsigned char * pix, int t_width, int t_height)
{
	pixels = pix;
	width = t_width;
	height = t_height;
	size = t_width*t_height;
}

float Image::calcColor(float green, float red, float blue){

	float max, min; 
	red /= 255;
	green /= 255;
	blue /= 255;
	float delta; 
	max = std::max(red, std::max(green, blue));
	min = std::min(red, std::min(green, blue));
	delta = max - min;

	float hue_temp, hue;
	if (red == max) {
		hue_temp = (green - blue) / (delta + 1e-20f);
		if(hue_temp < 0.0)
			hue_temp = hue_temp + 6.0;
	}
	else if (green == max)
		hue_temp = ((blue - red) / (delta + 1e-20f)) + 2;
	else
		hue_temp = ((red - green) / (delta + 1e-20f)) + 4;
	hue = hue_temp * 60;
	return hue;
}

void Image::setWidth(int width1){
	width = width1;
}

void Image::setHeight(int height1){
	height = height1;
}

int Image::getHeight() {
	return height;
}

int Image::getWidth() {
	return width;
}

double Image::getPixel(int i, int j) {
	if(j < 0) // nao temos esquerdo
		return pixels[i*width];
	else if(j > width-1) // nao temos direito
		return pixels[((i+1)*width)-1];
	else if(i < 0) // nao temos topo
		return pixels[j];
	else if(i > height-1) // nao temos baixo
		return pixels[((height-1)*width)+j];
	else
		return pixels[(i*width)+j];
}


double Image::calculateContrast(int i, int j){
	double topo_esquerdo = getPixel(i-1,j-1);
	double topo_direito = getPixel(i-1,j+1);
	double topo = getPixel(i-1,j);
	double esquerdo = getPixel(i,j-1);
	double direito = getPixel(i,j+1);
	double baixo_esquerdo = getPixel(i+1,j-1);
	double baixo_direito = getPixel(i+1,j+1);
	double baixo = getPixel(i+1,j);
	double middle_pixel = getPixel(i,j);
	double mean_luminance_adjacentes;

	mean_luminance_adjacentes = 
		(baixo + topo + topo_esquerdo + baixo_esquerdo + 
		esquerdo + direito + topo_direito + baixo_direito)/8;
	if(mean_luminance_adjacentes >= 0 && mean_luminance_adjacentes < 1){
		return mean_luminance_adjacentes;
	}

	return (std::abs(middle_pixel-mean_luminance_adjacentes))/std::abs(mean_luminance_adjacentes); 
}

int Image::getEdges(int i, int j){
	const int arr_size = 9;
	int edges[arr_size] = {-1,-1,-1,-1,8,-1,-1,-1,-1};

	double topo_esquerdo = getPixel(i-1,j-1);
	double topo_direito = getPixel(i-1,j+1);
	double topo = getPixel(i-1,j);
	double esquerdo = getPixel(i,j-1);
	double direito = getPixel(i,j+1);
	double baixo_esquerdo = getPixel(i+1,j-1);
	double baixo_direito = getPixel(i+1,j+1);
	double baixo = getPixel(i+1,j);
	double middle_pixel = getPixel(i,j);

	return (topo_esquerdo*edges[0]+topo*edges[1]+topo_direito*edges[2]+esquerdo*edges[3]+middle_pixel*edges[4]
	+ direito*edges[5] + baixo_esquerdo*edges[6] + baixo*edges[7] + baixo_direito*edges[8]);

}