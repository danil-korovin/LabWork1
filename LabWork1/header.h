/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/
#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <string>


struct BMP
{
public:
    void bmpRead(const std::string &namebmp);
    void bmpWrite(const std::string &namebmp);
    void Clockwise_rotation();
    void Counterclockwise_rotation();
    void GaussFilter();
    
private:
    uint8_t sp[2];
    struct BMPheader
    {
        uint32_t fsize;
        uint16_t creator1;
        uint16_t creator2;
        uint32_t offset;
    };
    struct BMPinfo
    {
        uint32_t biSize;
        int32_t width;
        int32_t height;
        uint16_t planes;
        uint16_t bitCount;
        uint32_t compres;
        uint32_t imBytes;
        int32_t biX;
        int32_t biY;
        uint32_t colors;
        uint32_t imcolors;
    };
    std::vector<uint8_t> pixdata;
    BMPheader Header;
    BMPinfo Info;
};


#endif
