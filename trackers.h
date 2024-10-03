//
// Created by pardusumsu on 02.10.2024.
//

#ifndef TRACKER_TESTER_CPP_TRACKERS_H
#define TRACKER_TESTER_CPP_TRACKERS_H

#include "iostream"

#include <opencv2/core/utility.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>


class trackers {
public:
    trackers();
    ~trackers();
    void run();
private:
    bool drawing = false;
    bool initialize_trackers = false;
    bool init = false;
    bool paused = false;
    cv::Rect roi;
    cv::Point start, end;
    cv::Mat frame;
    cv::Mat frame_nano;
    cv::Mat frame_mil;
    cv::Mat frame_kcf;
    cv::Mat frame_dasiamrpn;
    cv::Mat frame_goturn;
    cv::Mat frame_csrt;
    cv::Ptr<cv::TrackerNano> tracker_nano = cv::TrackerNano::create();
    cv::Ptr<cv::TrackerMIL> tracker_mil = cv::TrackerMIL::create();
    cv::Ptr<cv::TrackerKCF> tracker_kcf = cv::TrackerKCF::create();
    cv::Ptr<cv::TrackerDaSiamRPN> tracker_DaSiamRPN = cv::TrackerDaSiamRPN::create();
    cv::Ptr<cv::TrackerGOTURN> tracker_goturn = cv::TrackerGOTURN::create();
    cv::Ptr<cv::TrackerCSRT> tracker_csrt = cv::TrackerCSRT::create();
    int mouse_x, mouse_y;

    void mouse_callback(int event, int x, int y, int flags, void *userdata);
    static void onMouse(int event, int x, int y, int flags, void* userdata);
    void processFrame();
};


#endif //TRACKER_TESTER_CPP_TRACKERS_H
