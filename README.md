
https://github.com/user-attachments/assets/50027b65-3465-495d-9839-d0f2923d445f
# Tracker Tester CPP

A C++ program for testing and comparing the performance of different object tracking algorithms.

## Test Result

A sample test result video is included below:


https://github.com/user-attachments/assets/6eefaf46-1c5b-45f6-b6d5-56fba9962ed5
[test-in-6-tracker.mp4](test-in-6-tracker.mp4)

## Description

This program uses OpenCV to read a video file and apply different tracking algorithms to detect and track objects. The program displays the tracking results in real-time, allowing for easy comparison of the different algorithms.

## Algorithms Used

* Nano
* MIL
* KCF
* DaSiamRPN
* GOTURN
* CSRT

## Requirements

* OpenCV 4.10.0 or later
* C++ compiler (tested with GCC 13.2.0)

## Build and Run

To build and run the program, follow these steps:

### First you need to download following files

* * For GOTURN:
* goturn.prototxt and goturn.caffemodel: https://github.com/opencv/opencv_extra/tree/c4219d5eb3105ed8e634278fad312a1a8d2c182d/testdata/tracking
* * For DaSiamRPN:
* network:     https://www.dropbox.com/s/rr1lk9355vzolqv/dasiamrpn_model.onnx?dl=0
* kernel_r1:   https://www.dropbox.com/s/999cqx5zrfi7w4p/dasiamrpn_kernel_r1.onnx?dl=0
* kernel_cls1: https://www.dropbox.com/s/qvmtszx5h339a0w/dasiamrpn_kernel_cls1.onnx?dl=0
* * For NanoTrack:
* nanotrack_backbone: https://github.com/HonglinChu/SiamTrackers/blob/master/NanoTrack/models/nanotrackv2/nanotrack_backbone_sim.onnx
* nanotrack_headneck: https://github.com/HonglinChu/SiamTrackers/blob/master/NanoTrack/models/nanotrackv2/nanotrack_head_sim.onnx

To download files via terminal you can use following method
```
wget <url>
```

1. Clone the repository
2. Create a build directory and navigate to it
3. Run `cmake ..` to generate the build files
4. Run `make` to build the program
5. Run `./tracker_tester_cpp` to execute the program
