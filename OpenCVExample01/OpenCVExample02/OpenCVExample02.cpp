// OpenCVExample01.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <chrono>

#include <opencv2/opencv.hpp>

#pragma comment(lib, "opencv_core310.lib")
#pragma comment(lib, "opencv_imgcodecs310.lib")
#pragma comment(lib, "opencv_imgproc310.lib")
#pragma comment(lib, "opencv_highgui310.lib")

int main()
{
    // 符号なし8ビット整数 の 3ch(BGR) の画像を用意
    cv::Mat image = cv::imread("image.jpg", cv::IMREAD_COLOR);

    // 時間計測開始
    auto begin_time = std::chrono::high_resolution_clock::now();

    // 先頭ポインタ
    uint8_t* ptr = image.data;

    for (int y = 0; y < image.rows; ++y)
    {
        for (int x = 0; x < image.cols; ++x)
        {
            ptr[x * 3 + 0] = 255 - ptr[x * 3 + 0];  // B
            ptr[x * 3 + 1] = 255 - ptr[x * 3 + 1];  // G
            ptr[x * 3 + 2] = 255 - ptr[x * 3 + 2];  // R
        }

        ptr += image.step[0];
    }

    // 時間計測終了
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - begin_time).count() / 1000000.;
    std::cout << "elapsed time: " << duration << " 秒" << std::endl;

    cv::imshow("image", image);
    cv::waitKey();
    return 0;
}
