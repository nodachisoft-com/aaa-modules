#!/bin/bash
# ========================================================
# 依存ライブラリを ダウンロードしコンパイルする
# 前提コマンド：unzip, bash, Linux基本コマンド類, gcc, git
# ========================================================
build_ndc_cpp11_libs() {
  cd ./lib/

  # ndc-cpp11-libs のビルドを行う
  echo "[INFO] BUILD NDC-CPP11-LIBS BEGINS..."
  rm -rf ndc-cpp11-libs
  git clone https://github.com/nodachisoft-com/ndc-cpp11-libs.git
  cd ndc-cpp11-libs
  sh build.sh
  echo "[INFO] BUILD NDC-CPP11-LIBS COMPLETED!"
  cd ../../
}

# ========================================
# Windows + MinGW + gcc 環境で gtest を実行可能な環境を構築する
# 前提: git, mingw, cmake, make(mingw32-make) を choco でインストールしておくこと
# ========================================
build_gtest() {
  rm -rf ./tmp/*
  cd tmp
  git clone https://github.com/google/googletest.git
  cd googletest
  mkdir build
  cd build
  cmake -G "MinGW Makefiles" ..
  # コンパイル実施
  make

  # 出来上がったライブラリをプロジェクト参照先ライブラリのパスにコピー
  cd ../../../
  rm -rf lib/dev/gtest/lib/*
  cp -r tmp/googletest/build/lib/lib*.a lib/dev/gtest/lib/

  rm -rf lib/dev/gtest/include/*
  cp -r tmp/googletest/googlemock/include/gmock lib/dev/gtest/include/
  cp -r tmp/googletest/googletest/include/gtest lib/dev/gtest/include/
  rm -rf tmp/*
}

build_gtest
