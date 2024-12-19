/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/
#ifndef HEADER
#define HEADER

#include <iostream>
#include <vector>
#include <fstream>
#include <cstdint>

#pragma pack(push, 1)
struct bmpdata
{
    uint16_t type = 0x4D42; 
    uint32_t size = 0;  
    uint16_t res1 = 0;
    uint16_t res2 = 0;
    uint32_t offset = 54;
    uint32_t biSize = 40;
    int32_t width = 0;
    int32_t height = 0;
    uint16_t planes = 1;
    uint16_t bitCount = 24;
    uint32_t compres = 0;
    uint32_t imBytes = 0;
    int32_t biX = 0;
    int32_t biY = 0;
    uint32_t colors = 0;
    uint32_t imcolors = 0;
};


#pragma pack(pop)  

void bmpRead(const std::string& fileName, std::vector<unsigned char>& imData, bmpdata& header);
void bmpWrite(const std::string& fileName,  const std::vector<unsigned char>& imData, const bmpdata& header);
void clockwise_rotation(std::vector<unsigned char>& imData, int& width, int& height);
void counterclockwise_rotation(std::vector<unsigned char>& imData, int& width, int& height);
void GaussFilter(std::vector<unsigned char>& imData, int width, int height);

#endif
