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

int n = 1; //размер округи
int v = 9; //длина вектора

mat bubbleSort(mat x, int size)
{
    mat e = x;
    int j;
    for (int i = 0; i < size; i++)
    {
        for (j = 0; j < size - 1; j++)
        {
            if (e(0, j) > e(0, j + 1))
            {
                int temp = e(0, j + 1);
                e(0, j + 1) = e(0, j);
                e(0, j) = temp;
            }
        }
    }
    return e;
}

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
    start("images/4.jpg", "images/5.jpg", "result_images/out_image45.jpg");
    start("images/1.jpg", "images/3.jpg", "result_images/out_image13.jpg");

    return 0;
}
