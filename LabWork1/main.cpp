/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/

#include "header.h"


int main()
{
    BMP bmp;
    bmp.bmpRead("1.bmp");
    BMP pict1 = bmp;
    pict1.Clockwise_rotation();
    pict1.bmpWrite("Clockwise_rotation.bmp");
    BMP pict2 = bmp;
    pict2.Counterclockwise_rotation();
    pict2.bmpWrite("Counterclockwise_rotation.bmp");
    pict2.GaussFilter();
    pict2.bmpWrite("Gauss.bmp");
    return 0;
}
