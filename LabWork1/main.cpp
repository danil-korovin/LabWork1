/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/

#include "header.h"


int main()
{   
    bmpdata header;
    std::vector<unsigned char> imData;
    bmpRead("1.bmp", imData, header);
    clockwise_rotation(imData, header.width, header.height);
    header.size = sizeof(header) + imData.size();
    bmpWrite("clockwise_rotation.bmp", imData, header);
    bmpRead("1.bmp", imData, header); 
    counterclockwise_rotation(imData, header.width, header.height);
    header.size = sizeof(header) + imData.size();
    bmpWrite("counterclockwise_rotation.bmp", imData, header);  
    GaussFilter(imData, header.width, header.height);
    header.size = sizeof(header) + imData.size();
    bmpWrite("counterclockwise_rotation_gauss.bmp", imData, header);  
    return 0;
}
