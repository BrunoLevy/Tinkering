/*
 * Image-to-teletext conversion utility.
 * Bruno Levy 2022
 */

#include <SoftwareSerial.h>
#include <Minitel.h>

Minitel m(6,7);

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION

#include <stb/stb_image.h>
#include <stb/stb_image_resize.h>

/**
 * \brief The image encoded in grayscale.
 * \details Resolution is 80 x 144.
 *  It will be converted into 40 x 24 graphic characters of 2 x 3 pixels.
 */
unsigned char image_data[40*24*6];

// Set to 1 for smoother transitions (8 graylevels)
// Set to 2 for a more minitel-like rendering (4 graylevels)
int color_delta = 1;

/**
 * \brief Gets the grayscale intensity of a pixel.
 * \param[in] x , y the coordinates, in 0 .. 79 x 0 .. 23
 * \return the pixel intensity, in 0 .. 255
 */
static inline unsigned char getPixel(int x, int y) {
    return image_data[y*80+x];
}

/**
 * \brief Gets the "distance" between the color of a given pixel
 *   and a given color.
 * \param[in] x , y the coordinates, in 0 .. 79 x 0 .. 23
 * \param[in] c the color, in 0 .. 7
 */
static inline int colorDist(int x, int y, int c) {
    return std::abs(int(getPixel(x,y)) - (int(c) << 5));
}

/**
 * \brief Gets the "distance" between the color of a given pixel
 *   and the average of two given colors
 * \param[in] x , y the coordinates, in 0 .. 79 x 0 .. 23
 * \param[in] c1 , c2 the two colors, in 0 .. 7
 */
static inline int colorDist2(int x, int y, int c1, int c2) {
    return std::abs(int(getPixel(x,y)) - (int(c1 + c2) << 4));
}


/**
 * \brief Gets the minimum "distance" between the color of a given pixel
 *   and two given colors.
 * \param[in] x , y the coordinates, in 0 .. 79 x 0 .. 23
 * \param[in] c1 , c2 the two colors, in 0 .. 7
 */
static inline int colorDist(int x, int y, int c1, int c2) {
    return std::min(colorDist(x,y,c1), colorDist(x,y,c2));
}

/**
 * \brief Finds the nearest colors for a 2x3 block
 * \param[in] x , y the coordinates of the lower-left corner of the bloc, 
 *   in 0 .. 79 x 0 .. 23
 * \param[out] c1 , c2 the two colors, in 0 .. 7
 */
void nearestColors(int x, int y, int& c1, int & c2) {
    int bestSoFar = -1;
    for(int tc1 = 0; tc1 < 7; tc1 += color_delta) {
	for(int tc2 = tc1; tc2 < 7; tc2 += color_delta) {
	    int score =
		colorDist(x  ,y  ,tc1,tc2) +
		colorDist(x+1,y  ,tc1,tc2) +
		colorDist(x  ,y+1,tc1,tc2) +
		colorDist(x+1,y+1,tc1,tc2) +
		colorDist(x  ,y+2,tc1,tc2) +
		colorDist(x+1,y+2,tc1,tc2) ;
	    if(bestSoFar == -1 || score < bestSoFar) {
		bestSoFar = score;
		c1 = tc1;
		c2 = tc2;
	    }
	}
    }
}

/**
 * \brief Determines whether a block should be pixelated.
 * \details Pixelating a block makes it possible to simulate
 *  twice the number of graylevels (16 instead of 8)
 * \param[in] x , y the coordinates of the lower-left corner of the bloc, 
 *   in 0 .. 79 x 0 .. 23
 * \param[in,out] c1 , c2 the two colors, in 0 .. 7
 * \param[in,out] pixels a string of six characters 
 *   that indicates which pixels of the bloc should 
 *   be set to color c1 ('1') or color c2 ('0').
 */
bool pixelate(int x, int y, int& c1, int& c2, char* pixels) {
    int nb = 0;
    int nb_pix = 0;

    // Step 1: the set pixels vote to know whether their color c1
    // should be "dithered" with c2
    static int ofs[6][2] = {
	{0,0},
	{1,0},
	{0,1},
	{1,1},	
	{0,2},
	{1,2}
    };
    for(int i=0; i<6; ++i) {
	if(pixels[i] == '1') {
	    ++nb;
	    if(
		colorDist( x + ofs[i][0], y + ofs[i][1], c1) >
		colorDist2(x + ofs[i][0], y + ofs[i][1], c1, c2)
	    ) {
		++nb_pix;
	    }
	}
    }

    if(nb != 0) {
	return (nb_pix > nb/2);
    }

    // Step 2: if there was no pixel set, then we need to test whether
    // the entire bloc should be dithered.
    // We do so by setting all the pixels in the bloc, and call
    // pixelate() recursively to "vote".
    
    int avg_col = 0;
    for(int i=0; i<6; ++i) {
	avg_col += getPixel(x+ofs[i][0], y+ofs[i][1]);
	pixels[i] = '1';
    }
    avg_col /= 6;

    c1 = c2;
    c2 = (avg_col > c1) ? c1+color_delta : c1-color_delta;

    return pixelate(x,y,c1,c2,pixels);
}


/**
 * \brief Encodes a pixel in a bloc
 * \param[in] x , y the coordinates of the lower-left corner of the bloc, 
 *   in 0 .. 79 x 0 .. 23
 * \param[in,out] c1 , c2 the two colors, in 0 .. 7
 * \retval '1' if pixel color is nearer to c1 than to c2
 * \retval '0' otherwise
 */
static inline char encodePixel(int x, int y, int c1, int c2) {
    return colorDist(x,y,c1) < colorDist(x,y,c2) ? '1' : '0';
}

void loadImage(char* filename) {
    int x,y,n;
    unsigned char* data = stbi_load(filename, &x, &y, &n, 1);
    stbir_resize_uint8(data, x, y, 0, image_data, 40*2, 24*3, 0, 1);
    stbi_image_free(data);
}


void showImage() {

    static int cmap[8] = {
	BLACK,
	MAGENTA,
	RED,
	BLUE,
	GREEN,
	CYAN,
	YELLOW,
	WHITE
    };

    /*
    static bool image_loaded = false;
    if(!image_loaded) {
	if(global_argc == 2) {
	    loadImage(global_argv[1]);
	}
	image_loaded = true;
    }
    */

    m.graphicMode();
    m.moveCursorTo(1,1);
    m.useDefaultColors();

    static char s[7] = {0,0,0,0,0,0,0};
    for(int y=0; y<24; ++y) {
	for(int x=0; x<40; ++x) {

	    int c1, c2;
	    nearestColors(x*2,y*3,c1,c2);


	    s[0] = encodePixel(x*2  ,y*3  ,c1,c2);
	    s[1] = encodePixel(x*2+1,y*3  ,c1,c2);
	    s[2] = encodePixel(x*2  ,y*3+1,c1,c2);
	    s[3] = encodePixel(x*2+1,y*3+1,c1,c2);
	    s[4] = encodePixel(x*2  ,y*3+2,c1,c2);
	    s[5] = encodePixel(x*2+1,y*3+2,c1,c2);

	    if(pixelate(x*2,y*3,c1,c2,s)) {
		m.pixelate();
	    } else {
		m.noPixelate();
	    }

	    m.bgColor(cmap[c2]);
	    m.textColor(cmap[c1]);
	    
	    m.graphic(s);
	}
    }
}


void setup() {
}

void loop() {
    static int cur_image = 0;
    cur_image = (cur_image + 1) % (global_argc - 1);
    loadImage(global_argv[cur_image+1]);
    showImage();
    sleep(5);
}
