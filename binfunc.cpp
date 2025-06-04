/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/


#include "header.h"
#include <thread>
#include <future>

void BMP::bmpRead(const std::string &filename)
{
    std::ifstream bmpfile(filename.c_str(), std::ios::in | std::ios::binary);
    bmpfile.read((char*)(sp), sizeof(sp));
    bmpfile.read(reinterpret_cast<char*>(&Header), sizeof(BMPheader));
    bmpfile.read(reinterpret_cast<char*>(&Info), sizeof(BMPinfo));
    pixdata.resize(Info.height * Info.width * 3);
    bmpfile.seekg(Header.offset, std::ios::beg);
    for (int x = Info.height - 1; x >= 0; x--)
    {
        std::vector<uint8_t> arr(Info.width * 3);
        bmpfile.read(reinterpret_cast<char*>(arr.data()), Info.width*3);
        std::copy(arr.begin(), arr.end(), pixdata.begin() + (x * Info.width * 3));
        int pad = (4 - (Info.width * 3) % 4) % 4;
        bmpfile.ignore(pad);
    }
    bmpfile.close();
}


void BMP::bmpWrite(const std::string &filename)
{
    std::ofstream bmpfile(filename.c_str(), std::ios::out | std::ios::binary);
    bmpfile.write((char*)(&sp), sizeof(sp));
    bmpfile.write(reinterpret_cast<char*>(&Header), sizeof(BMPheader));
    bmpfile.write(reinterpret_cast<char*>(&Info), sizeof(BMPinfo));
    bmpfile.seekp(Header.offset, std::ios::beg);
    for (int x = Info.height - 1; x >= 0; x--)
    {
        std::vector<uint8_t> arr(Info.width * 3);
        std::copy(pixdata.begin() + (x * Info.width * 3), pixdata.begin() + ((x + 1) * Info.width * 3), arr.begin());
        bmpfile.write(reinterpret_cast<char*>(arr.data()), Info.width*3);
        size_t pad = ((Info.width * 3) % 4) % 4;
        for (size_t i = 0; i < pad; i++)
        {
            bmpfile.put(0);
        }
    }
    bmpfile.close();
}


void BMP::Clockwise_rotation()
{
    int width2 = Info.height;
    int height2 = Info.width;
    std::vector<uint8_t> pixdata2(width2 * height2 * 3);
    std::vector<std::future<void>> futures;
    int cores = std::thread::hardware_concurrency();
    std::cout<< "You have " << cores << " cores" << std::endl;
    int chunk = Info.height / cores;
    for (int t = 0; t < cores; ++t)
    {
        int start = t * chunk;
        int finish;
        if (t == cores - 1)
        {
            finish = Info.height;
        }
        else
        {
            finish = (t + 1) * chunk;
        }
        futures.push_back(std::async(std::launch::async, [this, &pixdata2, width2, height2, start, finish]()
        {
            for (int b = start; b < finish; b++)
            {
                for (int a = 0; a < Info.width; a++)
                {
                    int a2 = width2 - 1 - b;
                    int b2 = a;
                    int in1 = (b * Info.width + a) * 3;
                    int in2 = (b2 * width2 + a2) * 3;
                    for (int i = 0; i < 3; i++)
                    {
                        pixdata2[in2 + i] = pixdata[in1 + i];
                    }
                }
            }
        }));
    }
    for (auto &el: futures)
    {
        el.get();
    }
    Info.width = width2;
    Info.height = height2;
    pixdata.swap(pixdata2);
}


void BMP::Counterclockwise_rotation()
{
    int width2 = Info.height;
    int height2 = Info.width;
    std::vector<uint8_t> pixdata2(width2 * height2 * 3);
    std::vector<std::future<void>> futures;
    int cores = std::thread::hardware_concurrency();
    int chunk = Info.height / cores;
    for (int t = 0; t < cores; ++t)
    {
        int start = t * chunk;
        int finish;
        if (t == cores - 1)
        {
            finish = Info.height;
        }
        else
        {
            finish = (t + 1) * chunk;
        }
        futures.push_back(std::async(std::launch::async, [this, &pixdata2, width2, height2, start, finish]()
        {
            for (int b = start; b < finish; b++)
            {
                for (int a = 0; a < Info.width; a++)
                {
                    int a2 = b;
                    int b2 = height2 - 1 - a;
                    int in1 = (b * Info.width + a) * 3;
                    int in2 = (b2 * width2 + a2) * 3;
                    for (int i = 0; i < 3; i++)
                    {
                        pixdata2[in2 + i] = pixdata[in1 + i];
                    }
                }
            }
        }));
    }
    for (auto &el: futures)
    {
        el.get();
    }
    Info.width = width2;
    Info.height = height2;
    pixdata.swap(pixdata2);
}


void BMP::GaussFilter()
{
    float gauss[3][3] =
    {
        {0, 1, 0},
        {1, 5, 1},
        {0, 1, 0}
    };
    float sum = 9;
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            gauss[i][j] /= sum;
        }
    }
    std::vector<uint8_t> pixdata2(pixdata.size());
    std::vector<std::future<void>> futures;
    int cores = std::thread::hardware_concurrency();
    int chunk = (Info.height - 2) / cores;
    for (int t = 0; t < cores; ++t)
    {
        int start = t * chunk + 1;
        int finish;
        if (t == cores - 1)
        {
            finish = Info.height - 1;
        }
        else
        {
            finish = (t + 1) * chunk + 1;
        }
        futures.push_back(std::async(std::launch::async, [this, &pixdata2, &gauss, start, finish]()
        {
            for (int y = start; y < finish; y++)
            {
                for (int x = 1; x < Info.width - 1; x++)
                {
                    float red = 0, green = 0, blue = 0;
                    for (int a = 0; a < 3; a++)
                    {
                        for (int b = 0; b < 3; b++)
                        {
                            int pixelIndex = ((y + a - 1) * Info.width + (x + b - 1)) * 3;
                            red += pixdata[pixelIndex] * gauss[a][b];
                            green += pixdata[pixelIndex + 1] * gauss[a][b];
                            blue += pixdata[pixelIndex + 2] * gauss[a][b];
                        }
                    }
                    int outInd = (y * Info.width + x) * 3;
                    pixdata2[outInd] = std::min(std::max(0, static_cast<int>(red)), 255);
                    pixdata2[outInd + 1] = std::min(std::max(0, static_cast<int>(green)), 255);
                    pixdata2[outInd + 2] = std::min(std::max(0, static_cast<int>(blue)), 255);
                }
            }
        }));
    }
    for (auto &el: futures)
    {
        el.get();
    }
    pixdata = pixdata2;
}

