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

- ピクセル
- ポインタ
- グレースケール、RGB

## Pythonとの比較
