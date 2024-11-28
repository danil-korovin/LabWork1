/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/

#include "header.h"


void bmpRead(const std::string& fileName, std::vector<unsigned char>& imData, bmpdata& header)
{
    std::ifstream bmpfile(fileName, std::ios::binary);
    bmpfile.read(reinterpret_cast<char*>(&header), sizeof(header));
    int lineSize = ((header.width * header.bitCount + 31) / 8);
    imData.resize(lineSize * header.height);
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
    for (int a = 0; a < width; ++a)
    {
        for (int b = 0; b < height; ++b)
        {
            int l = (b * width + a)*3;
            int r = ((width - a - 1) * height + b)*3;
            for (int i = 0; i < 3; ++i)
            {
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
    for (int a = 0; a < width; ++a)
    {
        for (int b = 0; b < height; ++b)
        {
            int l = (b * width + a)*3;
            int r = (a * height + (height - b - 1))*3;
            for (int i = 0; i < 3; ++i)
            {
                dat[r + i] = imData[l + i];
            }

        }
    }
    imData = dat;
    std::swap(width, height);
}

void GaussFilter(std::vector<unsigned char>& imData, int width, int height)
{
    std::vector<unsigned char> outData(imData.size());
    int Gauss[3][3] =
    {
        {0, 1, 0},
        {1, 5, 1},
        {0, 1, 0}
    };
    int Gsum = 8;
    for (int y = 1; y < height - 1; ++y)
    {
        for (int x = 1; x < width - 1; ++x)
        {
            int red = 0, green = 0, blue = 0;
            for (int a = -1; a <= 1; ++a)
            {
                for (int b = -1; b <= 1; ++b)
                {
                    int pixInd = ((y + a) * width + (x + b)) * 3;
                    red += imData[pixInd] * Gauss[a + 1][b + 1];
                    green += imData[pixInd + 1] * Gauss[a + 1][b + 1];
                    blue += imData[pixInd + 2] * Gauss[a + 1][b + 1];
                }
            }
            int outInd = (y * width + x) * 3;
            outData[outInd] = std::min(std::max(red / Gsum, 0), 255);
            outData[outInd + 1] = std::min(std::max(green / Gsum, 0), 255);
            outData[outInd + 2] = std::min(std::max(blue / Gsum, 0), 255);
        }
    }
    imData = outData;
}
