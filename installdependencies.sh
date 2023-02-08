#!/usr/bin/sh
# ========================================================
# 依存ライブラリを ダウンロードしコンパイルする
# 前提コマンド：unzip, bash, Linux基本コマンド類, gcc, git
# ========================================================
cd ./lib/

# ndc-cpp11-libs のビルドを行う
echo "[INFO] BUILD NDC-CPP11-LIBS BEGINS..."
rm -rf ndc-cpp11-libs
git clone https://github.com/nodachisoft-com/ndc-cpp11-libs.git
cd ndc-cpp11-libs
sh build.sh
echo "[INFO] BUILD NDC-CPP11-LIBS COMPLETED!"
