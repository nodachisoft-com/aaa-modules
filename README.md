# 開発環境整備

installdependencies.sh を実行します。
実行には git、bash などが既に利用可能である必要があります。
Windows 環境では Cygwin ( MinGW ) があれば対応可能です。

これにより依存関係ライブラリ（ NDC-CPP11-LIBS ) が github よりダウンロードされ、
コンパイルした後、必要な動的ライブラリファイル や includes がワークスペース直下の lib 配下に格納されます。
