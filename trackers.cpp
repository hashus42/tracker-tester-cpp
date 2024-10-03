//
// Created by pardusumsu on 02.10.2024.
//

#include "trackers.h"

trackers::trackers() : mouse_x(0), mouse_y(0) {
    // Display the resulting frames
    cv::namedWindow("Nano_Tracker", cv::WINDOW_NORMAL);
    cv::resizeWindow("Nano_Tracker", 640, 480);
    cv::moveWindow("Nano_Tracker", 0, 0);

    cv::namedWindow("MIL_Tracker", cv::WINDOW_NORMAL);
    cv::resizeWindow("MIL_Tracker", 640, 480);
    cv::moveWindow("MIL_Tracker", 640, 0);

    cv::namedWindow("KCF_Tracker", cv::WINDOW_NORMAL);
    cv::resizeWindow("KCF_Tracker", 640, 480);
    cv::moveWindow("KCF_Tracker", 1280, 0);

    cv::namedWindow("DaSiamRPN_Tracker", cv::WINDOW_NORMAL);
    cv::resizeWindow("DaSiamRPN_Tracker", 640, 480);
    cv::moveWindow("DaSiamRPN_Tracker", 0, 530);

    cv::namedWindow("Goturn_Tracker", cv::WINDOW_NORMAL);
    cv::resizeWindow("Goturn_Tracker", 640, 480);
    cv::moveWindow("Goturn_Tracker", 640, 530);

    cv::namedWindow("CSRT_Tracker", cv::WINDOW_NORMAL);
    cv::resizeWindow("CSRT_Tracker", 640, 480);
    cv::moveWindow("CSRT_Tracker", 1280, 530);

    cv::setMouseCallback("Nano_Tracker", onMouse, this);
}

void trackers::mouse_callback(int event, int x, int y, int flags, void *userdata) {
    mouse_x = x;
    mouse_y = y;
    if (event == cv::EVENT_LBUTTONDOWN) {
        drawing = true;
        start = cv::Point(x, y);
    } else if (event == cv::EVENT_MOUSEMOVE) {
        if (drawing) {
            end = cv::Point(x, y);
            rectangle(frame, start, end, cv::Scalar(0, 255, 0), 2);
            imshow("Nano_Tracker", frame);
        }
    } else if (event == cv::EVENT_LBUTTONUP) {
        drawing = false;
        end = cv::Point(x, y);
        roi = cv::Rect(start, end);
        rectangle(frame, start, end, cv::Scalar(0, 255, 0), 2);
        initialize_trackers = true;
    }
}

void trackers::onMouse(int event, int x, int y, int flags, void* userdata) {
    auto* app = reinterpret_cast<trackers*>(userdata);
    app->mouse_callback(event, x, y, flags, userdata);
}

void trackers::processFrame() {
    double fps;
    cv::VideoCapture cap("../../tracker-tester-py/data/amman-stunt.mp4");

    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open camera\n";
        return;
    }

    for (;;) {
        int64 time_start = cv::getTickCount();
        cap >> frame;
        if (frame.empty()) break;

        cv::flip(frame, frame, 1);
        frame.copyTo(frame_nano);
        frame.copyTo(frame_mil);
        frame.copyTo(frame_kcf);
        frame.copyTo(frame_dasiamrpn);
        frame.copyTo(frame_goturn);
        frame.copyTo(frame_csrt);

        if (initialize_trackers) {
            tracker_nano->init(frame, roi);
            tracker_mil->init(frame, roi);
            tracker_kcf->init(frame, roi);
            tracker_DaSiamRPN->init(frame, roi);
            tracker_goturn->init(frame, roi);
            tracker_csrt->init(frame, roi);

            init = true;
            initialize_trackers = false;
        }

        if (init) {
            tracker_nano->update(frame, roi);
            cv::rectangle(frame_nano, roi, cv::Scalar(0, 255, 0), 2, 1); // green
            tracker_mil->update(frame, roi);
            cv::rectangle(frame_mil, roi, cv::Scalar(0, 0, 255), 2, 1); // blue
            tracker_kcf->update(frame, roi);
            cv::rectangle(frame_kcf, roi, cv::Scalar(0, 165, 255), 2, 1); // orange
            tracker_DaSiamRPN->update(frame, roi);
            cv::rectangle(frame_dasiamrpn, roi, cv::Scalar(128, 0, 0), 2, 1); // dark red
            tracker_goturn->update(frame, roi);
            cv::rectangle(frame_goturn, roi, cv::Scalar(255, 0, 127), 2, 1); // pink
            tracker_csrt->update(frame, roi);
            cv::rectangle(frame_csrt, roi, cv::Scalar(255, 255, 0), 2, 1); // yellow
        }



        // show fps and draw four lines simultaneously with mouse place
        fps = cv::getTickFrequency() / (cv::getTickCount() - time_start);
        cv::putText(frame_nano, "FPS: " + std::to_string((int)fps), cv::Point(10, 30),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(255, 255, 0));

        cv::line(frame, cv::Point(mouse_x, mouse_y), cv::Point(640, mouse_y), cv::Scalar(255, 255, 0), 1);
        cv::line(frame, cv::Point(mouse_x, mouse_y), cv::Point(0, mouse_y), cv::Scalar(255, 255, 0), 1);
        cv::line(frame, cv::Point(mouse_x, mouse_y), cv::Point(mouse_x, 480), cv::Scalar(255, 255, 0), 1);
        cv::line(frame, cv::Point(mouse_x, mouse_y), cv::Point(mouse_x, 0), cv::Scalar(255, 255, 0), 1);

        cv::putText(frame_nano, "Tracker: NANO", cv::Point(10, 60),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(0, 255, 0));
        cv::putText(frame_mil, "Tracker: MIL", cv::Point(10, 90),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(0, 0, 255));
        cv::putText(frame_kcf, "Tracker: KCF", cv::Point(10, 120),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(0, 165, 255));
        cv::putText(frame_dasiamrpn, "Tracker: DaSiamRPN", cv::Point(10, 150),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(128, 0, 0));
        cv::putText(frame_goturn, "Tracker: GOTURN", cv::Point(10, 180),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(255, 0, 127));
        cv::putText(frame_csrt, "Tracker: CSRT", cv::Point(10, 210),
                    cv::FONT_HERSHEY_COMPLEX, 1.0, CV_RGB(255, 255, 0));

        cv::imshow("Nano_Tracker", frame_nano);
        cv::imshow("MIL_Tracker", frame_mil);
        cv::imshow("KCF_Tracker", frame_kcf);
        cv::imshow("DaSiamRPN_Tracker", frame_dasiamrpn);
        cv::imshow("Goturn_Tracker", frame_goturn);
        cv::imshow("CSRT_Tracker", frame_csrt);

        int key = cv::waitKey(1) & 0xFF;
        if (key == 27 || key == 'q') break;
        else if (key == ' ') {
            paused = !paused;
            while (paused) {
                key = cv::waitKey(1) & 0xFF;
                if (key == ' ') paused = !paused;
                else if (key == 27 || key == 'q') break;
            }
        }
    }
}

void trackers::run() {
    processFrame();
}

trackers::~trackers() = default;
