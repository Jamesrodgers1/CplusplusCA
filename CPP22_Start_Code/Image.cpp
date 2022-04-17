//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include "Image.h"
#include "UsefulFunctions.h"

#define filterWidth 3
#define filterHeight 3


bool Image::load(string filename)
{
    ifstream ifs(filename, std::ios::binary);
    string magicNumber;
    ifs >> magicNumber;
    ifs >> this->w;
    ifs >> this->h;
    int p;
    ifs >> p;
    ifs.ignore(256, '\n');
    if(p==255)
    {
        delete[] pixels;
        pixels = new Rgb[w*h];
        unsigned char pix[3];
        for(int i = 0; i < w*h; i++)
        {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
            if(i < 100) {
//            cout << (int)pixels[i].r << (int)pixels[i].g << (int)pixels[i].b << endl;
            }
        }
        return true;
    }
    return false;

}
bool Image::loadRaw(string filename)
{
    return false;
}
bool Image::savePPM(string filename)


    {
        if (w == 0 || h == 0) { fprintf(stderr, "Can't save an empty image\n"); return false; }
        std::ofstream ofs;
        try {
            ofs.open(filename, std::ios::binary); // need to spec. binary mode for Windows users
            if (ofs.fail()) throw("Can't open output file");
            ofs << "P6\n" << w << " " << h << "\n255\n";
            unsigned char pixel[3];
            // loop over each pixel in the image, clamp and convert to byte format
            for (int i = 0; i < w * h; ++i) {
                pixel[1] = static_cast <unsigned char> (this->pixels[i].r);
                pixel[2] = static_cast <unsigned char> (this->pixels[i].g);
                pixel[3] = static_cast <unsigned char> (this->pixels[i].b);
                ofs.write(reinterpret_cast<char *>(pixel),3);
            }
            ofs.close();
        }
        catch (const char err) {
            fprintf(stderr, "%s\n", err);
            ofs.close();

        }
        return true;
    }



void Image::filterRed()
{
    for(int i = 0; i <  w * h; i++)
    {
        this->pixels[i].g = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterGreen()
{
    for(int i = 0; i <  w * h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].b = 0;
    }
}
void Image::filterBlue()
{
    for(int i = 0; i <  w * h; i++)
    {
        this->pixels[i].r = 0;
        this->pixels[i].g = 0;
    }
}
void Image::greyScale()
{
    int size = w * h;
    for (int i = 0; i < size; i++)
    {
        unsigned char greyscale= ((this->pixels[i].r) + (this->pixels[i].g) + (this->pixels[i].b))/ 3;
        this->pixels[i] = greyscale;
        this->pixels[i] = greyscale;
        this->pixels[i] = greyscale;
    }
}
void Image::flipHorizontal()
{
for (int i = 0; i < h; i++){
    for (int j = 0; j < w / 2; ++j) {
        swap(pixels[j + i * w], pixels[i * w + (w - j)]);
    }

    }
}


void Image::flipVertically()
{
    for (int i = 0; i < h / 2; i++) {
            for (int j = 0; j < w; j++) {
            swap(pixels[j + i * w], pixels[j + (h - 1 - i) * w]);
        }
    }
}
void Image::AdditionalFunction2() {
    for (int i = 0; i < w / 2; i++) {
        for (int j = 0; j < h; j++) {
            swap(pixels[j + i * h], pixels[j + (w - 1 - i) * h]);
        }
    }
}


void Image::AdditionalFunction3() {


    }

void Image::AdditionalFunction1()
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h ; j++)
        {
            swap(pixels[i,j],  pixels[h-1-j,i]);
        }
    }
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}

