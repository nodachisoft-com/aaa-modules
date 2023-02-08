# コンパイラ
CC  = g++
# コンパイルオプション
CFLAGS    = -g
CFLAGS   += -pthread

# Google Test 用実行ファイル名
RUN_TEST_EXEC_FILE  = ./debug/test.out

# お試しエントリポイント用実行ファイル名
RUN_TMP_ENTRY_EXEC_FILE  = ./debug/tmp_entry.out

# コンパイル対象のソースコード一覧を作成
# SECROOTから再帰的にソースファイルを検索 し
SRCROOT = ./src
SOURCES = $(shell find $(SRCROOT) -type f -name "*.cpp")


# テスト対象のソースコード
TEST_SRCROOT = ./test
TEST_SOURCES = $(shell find $(TEST_SRCROOT) -type f -name "test_*.cpp")

# お試しエントリポイントのソースコード
TMP_ENTRY_SRCROOT = ./test/tmp_entry
TMP_ENTRY_SOURCES = $(shell find $(TMP_ENTRY_SRCROOT) -type f -name "*.cpp")

# 依存関係ライブラリパス
DEPENDENCIES_INCDIR = -I./lib/ndc-cpp11-libs/publish/includes
DEPENDENCIES_LIBDIR  = -L./lib/ndc-cpp11-libs/publish/libs
DEPENDENCIES_LIBS = -lNdclibs

# オブジェクトファイル名
# OBJS    = $(SRCS:.cpp=.o)

# インクルードファイルのある test 用ディレクトリパス
TEST_INCDIR   = -I./lib/dev/gtest/include # Google Test 用インクルード
TEST_INCDIR  += -I./lib/dev # Test 共通定義用インクルード
# TEST_INCDIR += -I./lib/prod/cereal-1.3.2/include # Cereal 用

# test 用ライブラリファイルのあるディレクトリパス
TEST_LIBDIR  = -L./lib/dev/gtest/lib	# Google Test 用ライブラリ

# 追加する test 用ライブラリファイル
TEST_LIBS    = -lgtest_main
TEST_LIBS   += -lgtest





# ターゲット：コンパイル＆リンク で Google Test 実行ファイルを作成
$(RUN_TEST_EXEC_FILE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) $(TEST_SOURCES) -o $(RUN_TEST_EXEC_FILE) $(TEST_INCDIR) $(TEST_LIBDIR) $(TEST_LIBS) $(DEPENDENCIES_INCDIR)  $(DEPENDENCIES_LIBDIR) $(DEPENDENCIES_LIBS)

# ターゲット：コンパイル＆リンク で お試しの Entry Point 実行ファイルを作成
$(RUN_TMP_ENTRY_EXEC_FILE): $(SOURCES)
	$(CC) $(SOURCES) $(TMP_ENTRY_SOURCES) -o $(RUN_TMP_ENTRY_EXEC_FILE) $(DEPENDENCIES_INCDIR) $(DEPENDENCIES_LIBDIR) $(DEPENDENCIES_LIBS)

# テスト用ソースコードのコンパイル＆実行
all: clean $(RUN_TEST_EXEC_FILE) runtest

# 一時ファイル、実行ファイルを削除
clean:
	-rm -f $(RUN_TEST_EXEC_FILE) $(RUN_TMP_ENTRY_EXEC_FILE)
	-rm -f ./debug/*.bmp
	-rm -rf ./debug/*

# Google Test の実行
runtest:
	$(RUN_TEST_EXEC_FILE)

buildentry: clean $(RUN_TMP_ENTRY_EXEC_FILE) run

run:
	$(RUN_TMP_ENTRY_EXEC_FILE)
