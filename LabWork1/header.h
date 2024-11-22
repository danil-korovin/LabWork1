/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/
#ifndef HEADER
#define HEADER

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

#pragma pack(1)
#pragma once


#pragma pack(1)

struct bmpdata
{
    uint16_t type; 
    uint32_t size;  
    uint16_t res1;
    uint16_t res2;
    uint32_t offset;
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

#pragma pack(push, f)
#pragma pack(pop)  

void bmpRead(const std::string& fileName, std::vector<unsigned char>& imData, bmpdata& header);
void bmpWrite(const std::string& fileName,  const std::vector<unsigned char>& imData, const bmpdata& header);
void clockwise_rotation(std::vector<unsigned char>& imData, int& width, int& height);
void counterclockwise_rotation(std::vector<unsigned char>& imData, int& width, int& height);

#endif
