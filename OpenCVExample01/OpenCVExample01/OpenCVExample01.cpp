// OpenCVExample01.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "opencv_core310.lib")
#pragma comment(lib, "opencv_imgcodecs310.lib")
#pragma comment(lib, "opencv_imgproc310.lib")
#pragma comment(lib, "opencv_highgui310.lib")

int main()
{
    cv::Mat image = cv::Mat::zeros(480, 640, CV_8UC3);
    cv::circle(image, cv::Point(320, 240), 100, CV_RGB(255, 255, 0), 10);
    cv::imshow("image", image);
    cv::waitKey();
    return 0;
}
