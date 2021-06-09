# 開発環境

開発環境は何でも良いのですが、今回は、以下の構成で行います。

- OS: Windows
- IDE: Visual Studio 2019 Professional

Visual Studio Community でも大丈夫です。

# OpenCVを使えるように準備する

OpenCVを使えるように準備する方法は、いくつかあります。

- OpenCV のリポジトリを github から取得して、 CMake する。
  - 最新版を使いたいならコレ。
  - CMake しないといけないので Windows の場合はちょっと面倒。
- インストーラーを入手して、インストールして使う。
- NuGet で入手する。
  - あまり更新されておらず、ちょっと古め。
  - gitでリポジトリを共有している場合、 NuGet を使ったプロジェクトをビルドするときに、自動的に取得してくれる。
  - インクルードパスなどの設定もほぼ自動的に行われる。
  - バージョンの変更も容易（古いけど）

Visual Studio で使う場合は、 NuGet を使うとすごく簡単なのでオススメです。
※ただし、更新があまりされていないので、バージョンは古めです。

NuGet で OpenCV を使えるようにする方法を説明します。

1. Visual Studio を立ち上げる

2. 「新しいプロジェクトの作成」を選ぶ

3. フィルターを 「C++」, 「Windows」 にして、「コンソールアプリ」を選択する。

4. 適当にプロジェクト名を入力して、作成する。

5. メニュー「プロジェクト」→「NuGetパッケージの管理」を選択する。
（もしくは、ソリューションエクスプローラ上のプロジェクト名を右クリックして、「NuGetパッケージの管理」を選択）

6. 「参照」をクリックして、検索欄に「opencv.win.native」と入力。

7. 「opencv.win.native」と、「opencv.win.native.redist」をインストール

8. 適当にプログラムを書く。

```cpp
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
```

9. 「プロジェクトのプロパティ」を表示し、「リンカ」→「全般」→「追加のライブラリディレクトリ」に、以下を追加する。を追加する。
（インクルードディレクトリは自動で設定されるけど、ライブラリパスは設定しないといけない。）

```text
../packages/opencv.win.native.310.3.0/build/native/lib/x64/v140/Release
```

10. 「ビルドイベント」→「ビルド後のイベント」に、以下のコマンドを入力する。
（手動でコピーしても良いが、コマンド書いておけば、リポジトリを共有した場合に幸せになれる。）

```bat
copy /y "..\packages\opencv.win.native.redist.310.3.0\build\native\bin\x64\v140\Release\opencv_core310.dll" "$(OutDir)"
copy /y "..\packages\opencv.win.native.redist.310.3.0\build\native\bin\x64\v140\Release\opencv_imgcodecs310.dll" "$(OutDir)"
copy /y "..\packages\opencv.win.native.redist.310.3.0\build\native\bin\x64\v140\Release\opencv_imgproc310.dll" "$(OutDir)"
copy /y "..\packages\opencv.win.native.redist.310.3.0\build\native\bin\x64\v140\Release\opencv_highgui310.dll" "$(OutDir)"
copy /y "..\packages\opencv.win.native.redist.310.3.0\build\native\bin\x64\v140\Release\opencv_videoio310.dll" "$(OutDir)"
```

11. [F5]キーを押して、ビルド→実行する。

12. 黄色い輪っかが表示されれば成功！
