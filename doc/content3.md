# C++でOpenCVのアプリを作る

- opencv highgui で作る簡単なやつ
  - カメラ映像を使って、画像をキャプチャ。
  - キャプチャした画像をリアルタイムに画像処理する。
  - トラックバーでパラメータを変更できるようにする。
  - [サンプルプログラム1：マンガっぽく画像処理](../OpenCVExample01/CameraExample)
  - [サンプルプログラム2：顔・目検出](../OpenCVExample01/FaceDetectionExample)

- WinForms でアプリ作る
  - OpenCVで作った画像を、画面に表示する。
  - 弊社アプリ： AdaWatcher
  - そんなに難しいことはしていないです。
    - cv::VideoCapture で画像をキャプチャ → cv::Mat
    - OpenCVの関数を使って、表示したい内容を cv::Mat に描画
    - cv::Mat を Bitmap に変換
    - Bitmap を画面に表示
