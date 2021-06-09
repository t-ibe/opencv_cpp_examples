// CameraExample.cpp : カメラ映像をアニメっぽい感じに変換してリアルタイム表示する
//

#include <iostream>
#include <opencv2/opencv.hpp>

#pragma comment(lib, "opencv_core310.lib")
#pragma comment(lib, "opencv_imgcodecs310.lib")
#pragma comment(lib, "opencv_imgproc310.lib")
#pragma comment(lib, "opencv_highgui310.lib")
#pragma comment(lib, "opencv_videoio310.lib")


// ピクセル値のクラスタリング
void cluster_by_pixel(const cv::Mat& src, cv::Mat& dest, int k)
{
    // 画像を1列の行列に変形
    cv::Mat points;
    src.convertTo(points, CV_32FC3);
    points = points.reshape(3, src.rows * src.cols);

    // RGB空間でk-meansを実行
    cv::Mat_<int> clusters(points.size(), CV_32SC1);
    cv::Mat centers;

    // クラスタ対象，クラスタ数，（出力）クラスタインデックス，
    // 停止基準，k-meansの実行回数，手法，（出力）クラスタ中心値
    cv::kmeans(points, k, clusters,
        cvTermCriteria(CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1.0), 1, cv::KMEANS_PP_CENTERS, centers);

    // 中心値を 32FU3 → 8UC3 に変換
    std::vector<cv::Vec3b> centers_8uc3(k);
    for (int i = 0; i < k; ++i) {
        auto& color = centers.at<cv::Vec3f>(i, 0);
        auto& table = centers_8uc3[i];
        table[0] = cv::saturate_cast<uchar>(color[0]);
        table[1] = cv::saturate_cast<uchar>(color[1]);
        table[2] = cv::saturate_cast<uchar>(color[2]);
    }

    // すべてのピクセル値をクラスタ中心値で置き換え
    dest = cv::Mat(src.size(), src.type());
    auto it = dest.begin<cv::Vec3b>();
    auto end = dest.end<cv::Vec3b>();
    for (int i = 0; it != end; ++it, ++i) {
        *it = centers_8uc3[clusters(i)];
    }
}


int main()
{
    // ウィンドウの作成
    cv::namedWindow("camera", cv::WINDOW_AUTOSIZE);
    cv::namedWindow("image", cv::WINDOW_AUTOSIZE);

    // トラックバーの作成
    int cluster_count = 15;
    cv::createTrackbar("cluster", "image", &cluster_count, 50);

    int thresh = 25;
    cv::createTrackbar("thresh", "image", &thresh, 255);

    // ビデオキャプチャーの作成
    cv::VideoCapture cap(0);

    do {
        // キャプチャー
        cv::Mat frame;
        cap >> frame;

        if (frame.empty())
            break;

        // カメラ画像を表示
        cv::imshow("camera", frame);

        // クラスタリング
        cv::Mat clustered;
        cluster_by_pixel(frame, clustered, cluster_count);

        // グレースケール化
        cv::Mat gray;
        cv::cvtColor(frame, gray, CV_BGR2GRAY);

        // エッジ抽出
        cv::Mat edge_x;
        cv::Mat edge_y;
        cv::Sobel(gray, edge_x, CV_8U, 1, 0, 3);
        cv::Sobel(gray, edge_y, CV_8U, 0, 1, 3);
        cv::Mat edge = abs(edge_x) + abs(edge_y);
        cv::convertScaleAbs(edge, edge, 1, 0);

        // 二値化
        cv::Mat binary;
        cv::threshold(edge, binary, thresh, 255, cv::THRESH_BINARY_INV /*| cv::THRESH_OTSU*/);

        // グレースケール→カラー
        cv::Mat binary_color;
        cv::cvtColor(binary, binary_color, CV_GRAY2BGR);

        // AND 合成
        cv::Mat image = binary_color & clustered;

        // 変換した画像を表示
        cv::imshow("image", image);

    } while (cv::waitKey(1) == -1);

    return 0;
}
