#REPORT
##Korovin Danil Pavlovich, group 24.B81-mm
###This test is performed on image "1.bmp" with a size of 8.4 MB on a virtual machine with 4 cores.
####Not parallel programming
The previous solution did not use parallelization.
```
Reading time: 13 ms
Clockwise_rotation time: 65 ms
Writing Clockwise_rotation time: 10 ms
Counterclockwise _rotation time: 56 ms
Writing counterclockwise_rotation time: 10 ms
Gauss filter time: 323 ms
Writing Gauss filter time: 10 ms
Total execution time: 487 ms
```
####Parallel programming
The new solution uses parallel programming (future objects) to perform 90 degree right and left rotations and a Gaussian filter. I do not use parallel programming for reading and writing images, because it will not gains significant performance result and may impact read and write integrity.
```
Reading time: 21 ms
Clockwise_rotation time: 33 ms
Writing Clockwise_rotation time: 10 ms
Counterclockwise_rotation time: 17 ms
Writing counterclockwise_rotation time: 11 ms
Gauss filter time: 86 ms
Writing Gauss filter time: 10 ms
Total execution time: 188 ms
```
For virtual box that has 4 cores, the parallel program runs approximately 2.6 times faster. For more cores, the program will run even faster. The Gaussian Filter had the biggest impact on program execution time, because the Gaussian Filter requires a relatively large amount of computation for each pixel.
####Reasons:
1. The parallel code splits the workload across multiple cores.
2. Dividing the image into chunks helps the different cores work properly.
