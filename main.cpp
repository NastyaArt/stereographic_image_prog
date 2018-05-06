#include <QCoreApplication>

#include <iostream>
#include <vector>

#include <CImg.h>
#include <armadillo>

#define cimg_imagemagick_path "/users/thatsme/local/bin/convert"
#define ARMA_DONT_USE_WRAPPER

using namespace std;
using namespace cimg_library;
using namespace arma;

int imageWidth; //ширина изображения
int imageHeight;  //высота  изображения

void start(const char * file1, const char * file2, const char *outputFile)
{
    cout << "Start..." << endl;
    CImg <unsigned char> image1(file1);
    CImg <unsigned char> image2(file2);
    if (image1.width()!=image2.width() || image1.height()!=image2.height())
        return;

    imageWidth=image1.width();
    imageHeight=image1.height();

    CImg <float> image_out(imageWidth, imageHeight, 1, 3, 0);

    for (int indexW = 0; indexW < imageWidth; indexW++){
        for (int indexH = 0; indexH < imageHeight; indexH++){
            double color[3];
            color[0] = (int)image1(indexW, indexH, 0, 0);
            color[1] = (int)image2(indexW, indexH, 0, 1);
            color[2] = (int)image2(indexW, indexH, 0, 2);
            image_out.draw_point(indexW, indexH, color);
        }
    }
    image_out.save(outputFile);
    cout << "Finish" << endl;
}

int main()
{
    start("images/1.jpg", "images/2.jpg", "result_images/out_image12.jpg");

    start("images/6.jpg", "images/7.jpg", "result_images/out_image67.jpg");
    return 0;
}
