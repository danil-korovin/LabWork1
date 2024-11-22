/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/

#include "header.h"

void bmpRead(const std::string& fileName, std::vector<unsigned char>& imData, bmpdata& header)
{
    std::ifstream bmpfile(fileName, std::ios::binary);
    bmpfile.read(reinterpret_cast<char*>(&header), sizeof(header));
    int w = header.width;
    int h = header.height;
    int line = (((w * header.bitCount) + 31) / 8);
    imData.resize(line * h);
    bmpfile.read(reinterpret_cast<char*>(imData.data()), imData.size());
    bmpfile.close();
}

void bmpWrite(const std::string& fileName,  const std::vector<unsigned char>& imData, const bmpdata& header)
{
    std::ofstream bmpfileOut(fileName, std::ios::binary);
    bmpfileOut.write(reinterpret_cast<const char*>(&header), sizeof(header));
    bmpfileOut.write(reinterpret_cast<const char*>(imData.data()), imData.size());
    bmpfileOut.close();
}

void clockwise_rotation(std::vector<unsigned char>& imData, int& width, int& height)
{
    std::vector<unsigned char> dat(imData.size());
    for (int a = 0; a < width; a++)
    {
        for (int b = 0; b < height; b++)
        {
            int l = (b * width + a)*3;
            int r = ((width - a - 1) * height + b)*3;
            for (int i = 0; i < 3; ++i) {
            	dat[r + i] = imData[l + i];
            }

        }
    }
    imData = dat;
    std::swap(width, height);
}

void counterclockwise_rotation(std::vector<unsigned char>& imData, int& width, int& height)  
{  
    std::vector<unsigned char> dat(imData.size());
    for (int a = 0; a < width; a++)  
    {  
        for (int b = 0; b < height; b++)  
        {  
            int l = (b * width + a)*3;
            int r = (a * height + (height - b - 1))*3;  
            for (int i = 0; i < 3; ++i) {
            	dat[r + i] = imData[l + i];
            }

        }  
    }  
    imData = dat;
    std::swap(width, height);
}

