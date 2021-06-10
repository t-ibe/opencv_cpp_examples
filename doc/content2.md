# cv::Mat

OpenCV Cookbook にいい感じにまとまっているので、そこに載っている重要そうなところを見ていきましょう。

## cv::Matについて

cv::Matの概要：
http://opencv.jp/cookbook/opencv_mat.html

マルチチャンネルと多次元配列：
http://opencv.jp/cookbook/opencv_mat.html#id2

浅いコピーと深いコピー：
http://opencv.jp/cookbook/opencv_mat.html#id3

連続データと不連続データ：
http://opencv.jp/cookbook/opencv_mat.html#id4

cv::Matを初期化する：
http://opencv.jp/cookbook/opencv_mat.html#id9

cv::Matの様々なプロパティ：
http://opencv.jp/cookbook/opencv_mat.html#mat-various-properties

## 画像処理の関数

いろいろ画像処理：
http://opencv.jp/cookbook/opencv_img.html

描画処理：
http://opencv.jp/cookbook/opencv_drawing.html

# ピクセルを直接いじる

別にC++じゃなくても、Pythonでも同じことはできます。

C++で作るときのメリットとしては、以下
- 高速にピクセルごとに計算したい場合
- GUIアプリケーションをつくりたい場合

## C++でピクセル単位に計算する場合

- データ構造

図を入れる

- cv::Mat

```cpp
#include <iostream>
#include <opencv2/core/core.hpp>

int
main(int argc, char *argv[])
{
  cv::Mat m1(4, 5, CV_32FC(5));  //5x4
  cv::Rect roi_rect(0, 0, 3, 4); //4x3
  cv::Mat r1(m1, roi_rect);

  // 行数
  std::cout << "rows:" << r1.rows <<std::endl;
  // 列数
  std::cout << "cols:" << r1.cols << std::endl;
  // 次元数
  std::cout << "dims:" << r1.dims << std::endl;
  // サイズ（2次元の場合）
  std::cout << "size[]:" << r1.size().width << "," << r1.size().height << std::endl;
  // ビット深度ID
  std::cout << "depth (ID):" << r1.depth() << "(=" << CV_32F << ")" << std::endl;
  // チャンネル数
  std::cout << "channels:" << r1.channels() << std::endl;
  // （複数チャンネルから成る）1要素のサイズ [バイト単位]
  std::cout << "elemSize:" << r1.elemSize() << "[byte]" << std::endl;
  // 1要素内の1チャンネル分のサイズ [バイト単位]
  std::cout << "elemSize1 (elemSize/channels):" << r1.elemSize1() << "[byte]" << std::endl;
  // 要素の総数
  std::cout << "total:" << r1.total() << std::endl;
  // ステップ数 [バイト単位]
  std::cout << "step:" << r1.step << "[byte]" << std::endl;
  // 1ステップ内のチャンネル総数
  std::cout << "step1 (step/elemSize1):" << r1.step1()  << std::endl;
  // データは連続か？
  std::cout << "isContinuous:" << (r1.isContinuous()?"true":"false") << std::endl;
  // 部分行列か？
  std::cout << "isSubmatrix:" << (r1.isSubmatrix()?"true":"false") << std::endl;
  // データは空か？
  std::cout << "empty:" << (r1.empty()?"true":"false") << std::endl;
}
```

ピクセル値を直接操作してみます。

下記の例は、ネガポジ反転で、白と黒を逆にしています。

```cpp
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
```

Pythonで、同じことをやろうとすると？

```python
import numpy
import cv2

import timeit

image = cv2.imread("image.jpg", cv2.IMREAD_COLOR)

begin_time = timeit.default_timer()
for y in range(image.shape[0]):
    for x in range(image.shape[1]):
        image[y, x, 0] = 255 - image[y, x, 0]
        image[y, x, 1] = 255 - image[y, x, 1]
        image[y, x, 2] = 255 - image[y, x, 2]

end_time = timeit.default_timer()
print("elapsed time: {} 秒", end_time - begin_time)

cv2.imshow("image", image)
cv2.waitKey(0)
```

速度比較

```
C++    :  0.002617 秒
Python :  9.487495 秒
```
