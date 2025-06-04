/* Korovin Danil st128737@student.spbu.ru
   LabWork1
*/

#include "header.h"
#include <chrono>

int main()
{
    BMP bmp;
    auto start_read = std::chrono::high_resolution_clock::now();
    bmp.bmpRead("1.bmp");
    auto end_read = std::chrono::high_resolution_clock::now();
    auto duration_read = std::chrono::duration_cast<std::chrono::milliseconds>(end_read - start_read);
    std::cout << "Reading time: " << duration_read.count() << " ms" << std::endl;
    BMP pict1 = bmp;
    auto start_clockwise = std::chrono::high_resolution_clock::now();
    pict1.Clockwise_rotation();
    auto end_clockwise = std::chrono::high_resolution_clock::now();
    auto duration_clockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end_clockwise - start_clockwise);
    std::cout << "Clockwise_rotation time: " << duration_clockwise.count() << " ms" << std::endl;
    auto start_write_clockwise = std::chrono::high_resolution_clock::now();
    pict1.bmpWrite("Clockwise_rotation.bmp");
    auto end_write_clockwise = std::chrono::high_resolution_clock::now();
    auto duration_write_clockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end_write_clockwise - start_write_clockwise);
    std::cout << "Writing Clockwise_rotation time: " << duration_write_clockwise.count() << " ms" << std::endl;
    BMP pict2 = bmp;
    auto start_counterclockwise = std::chrono::high_resolution_clock::now();
    pict2.Counterclockwise_rotation();
    auto end_counterclockwise = std::chrono::high_resolution_clock::now();
    auto duration_counterclockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end_counterclockwise - start_counterclockwise);
    std::cout << "Counterclockwise_rotation time: " << duration_counterclockwise.count() << " ms" << std::endl;
    auto start_write_counterclockwise = std::chrono::high_resolution_clock::now();
    pict2.bmpWrite("Counterclockwise_rotation.bmp");
    auto end_write_counterclockwise = std::chrono::high_resolution_clock::now();
    auto duration_write_counterclockwise = std::chrono::duration_cast<std::chrono::milliseconds>(end_write_counterclockwise - start_write_counterclockwise);
    std::cout << "Writing counterclockwise_rotation time: " << duration_write_counterclockwise.count() << " ms" << std::endl;
    auto start_gauss = std::chrono::high_resolution_clock::now();
    pict2.GaussFilter();
    auto end_gauss = std::chrono::high_resolution_clock::now();
    auto duration_gauss = std::chrono::duration_cast<std::chrono::milliseconds>(end_gauss - start_gauss);
    std::cout << "Gauss filter time: " << duration_gauss.count() << " ms" << std::endl;
    auto start_write_gauss = std::chrono::high_resolution_clock::now();
    pict2.bmpWrite("Gauss.bmp");
    auto end_write_gauss = std::chrono::high_resolution_clock::now();
    auto duration_write_gauss = std::chrono::duration_cast<std::chrono::milliseconds>(end_write_gauss - start_write_gauss);
    std::cout << "Writing Gauss filter time: " << duration_write_gauss.count() << " ms" << std::endl;
    auto total_duration = duration_read + duration_clockwise + duration_write_clockwise + duration_counterclockwise + duration_write_counterclockwise + duration_gauss + duration_write_gauss;
    std::cout << "Total execution time: " << total_duration.count() << " ms" << std::endl;
    return 0;
}
