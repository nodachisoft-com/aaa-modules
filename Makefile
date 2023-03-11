# =========================================================================
# 主要なターゲットは以下の通り。
#
#  make test       : 本体プログラム、テストコード をコンパイルし単体テスト実行
#  make test-テスト対象クラス  : gtest の gtest_filter オプションを使用した単体テストを実行
#  make testtmp    : お試しテストエントリコードを gtest を使わずにビルドし実行
#  make publish    : 最終出力先のプログラム（ライブラリ）、includes を作成
#  make clean      : 生成物を全てクリアする
#

# デバッグ用メッセージの ESCAPE SEQUENCE カラー設定
MSG_B="\033[0;36m[INFO `date "+%H:%M:%S"`] "
MSG_E=" \033[0m"

# コンパイラ
CXX  = g++

# コンパイルオプション
#  -g         : デバッグ情報付与
#  -pthread   : std::thread 利用
#  -std=c++17 : C++17 規格でコンパイル
#  -Wall      : 警告を出力
CFLAGS    = -g
CFLAGS   += -pthread
CFLAGS   += -std=c++17
CFLAGS   += -Wall
CFLAGS   += -Werror

# テストコード用コンパイルオプション
TEST_CLAGS = -pthread
TEST_CLAGS = -std=c++17

# src 用 依存関係ライブラリパス
DEPENDENCIES_INCDIR = -I./lib/ndc-cpp11-libs/includes
DEPENDENCIES_LIBDIR  = -L./lib/ndc-cpp11-libs/libs
DEPENDENCIES_LIBS = -lNdclibs

# test src 用 依存関係ライブラリパス
DEPENDENCIES_TEST_INCDIR  = $(DEPENDENCIES_INCDIR)
DEPENDENCIES_TEST_INCDIR += -I./lib/dev/gtest/include
DEPENDENCIES_TEST_INCDIR += -I./lib/dev

DEPENDENCIES_TEST_LIBDIR  = $(DEPENDENCIES_LIBDIR)
DEPENDENCIES_TEST_LIBDIR += -L./lib/dev/gtest/lib

DEPENDENCIES_TEST_LIBS  = $(DEPENDENCIES_LIBS)
DEPENDENCIES_TEST_LIBS += -lgtest_main
DEPENDENCIES_TEST_LIBS += -lgtest


# お試しエントリポイント用実行ファイル名
RUN_TMP_ENTRY_EXEC_FILE  = ./debug/tmp_entry.out

# コンパイル対象のソースコード一覧を作成
# SECROOTから再帰的にソースファイルを検索 し
OBJROOT = tmp/compile/src
ifeq "$(strip $(OBJROOT))" ""
	OBJROOT=.
endif

# ===============================================
# プログラム本体のソースコード、ターゲット設定
# SECROOTから再帰的にソースファイルを検索する
SRCROOT = src
SRCDIRS = $(shell find $(SRCROOT) -type d)
SOURCES = $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.cpp))

OBJSRCS = $(SOURCES:$(SRCROOT)/%=%)
OBJECTS = $(addprefix $(OBJROOT)/, $(OBJSRCS:.cpp=.o))

DEPENDS = $(OBJECTS:.o=.d)

# ===============================================
# テスト用 SRC / OBJECT を定義
TEST_OBJROOT = tmp/compile/test
ifeq "$(strip $(TEST_OBJROOT))" ""
	TEST_OBJROOT=.
endif

TEST_SRCROOT = test
TEST_SRCDIRS = $(shell find $(TEST_SRCROOT) -type d)
TEST_SOURCES = $(foreach dir, $(TEST_SRCDIRS), $(wildcard $(dir)/test_*.cpp))

TEST_OBJSRCS = $(TEST_SOURCES:$(TEST_SRCROOT)/%=%)
TEST_OBJECTS = $(addprefix $(TEST_OBJROOT)/, $(TEST_OBJSRCS:.cpp=.o))

TEST_DEPENDS = $(TEST_OBJECTS:.o=.d)

# ===============================================
# 本番ライブラリ出力用 ビルド設定
# ライブラリを生成し、リリース用 include ファイルを publish にコピーする
PUBLISH_TARGET = ./publish/libs/libAaaCommon.a
$(PUBLISH_TARGET): $(OBJECTS)
	@echo -e ${MSG_B}============================================${MSG_E}
	@echo -e ${MSG_B}Publishing Library files and Includes files.${MSG_E}
	@echo -e ${MSG_B}============================================${MSG_E}
	-mkdir ./publish/libs
	ar rcs $@ $^
	-mkdir ./publish/includes
	find ./src -type d | xargs -I{} mkdir -p ./publish/includes/{}
	find ./src -type f -name "*.hpp" | xargs -I{} cp {} ./publish/includes/{}
	@echo -e ${MSG_B}DONE.${MSG_E}

.PHONY: ObjectTargetFlow
ObjectTargetFlow: ObjectPre $(OBJECTS)
	@echo -e ${MSG_B}DONE.${MSG_E}

.PHONY: ObjectPre
ObjectPre:
	@echo -e ${MSG_B}Compile Sources.${MSG_E}


# ===============================================
# 単体テスト実行用 ビルド設定
# Google Test 用実行プログラムを生成する
TEST_TARGET = ./debug/test.out
$(TEST_TARGET): ObjectTargetFlow TestTargetPre TestTargetMain
		@echo -e ${MSG_B}DONE.${MSG_E}

RUN_TMP_ENTRY_EXEC_FILE  = ./debug/tmp_entry.out
$(RUN_TMP_ENTRY_EXEC_FILE): ObjectTargetFlow RunTmpEntryTargetPre RunTmpEntryTargetMain
		@echo -e ${MSG_B}DONE.${MSG_E}

.PHONY: TestTargetPre
TestTargetPre:
	@echo -e ${MSG_B}Compile Test Sources.${MSG_E}


# テスト用オブジェクト、メインモジュール用オブジェクトをリンクして UT 用 EXE を出力する
.PHONY: TestTargetMain
TestTargetMain: $(OBJECTS) $(TEST_OBJECTS)
	@echo -e ${MSG_B}Compile DONE.${MSG_E}
	@echo -e ${MSG_B}Linking Unit-Test Executable.${MSG_E}
	$(CXX) $(CFLAGS) -o $(TEST_TARGET) $^ $(DEPENDENCIES_TEST_LIBDIR) $(DEPENDENCIES_TEST_LIBS)

# お試し用コンパイル開始メッセージ
.PHONY: RunTmpEntryTargetPre
RunTmpEntryTargetPre:
	@echo -e ${MSG_B}Compile Sources.${MSG_E}

# お試し用テストエントリポイント、メインモジュール用オブジェクトをリンクしてお試し用 EXE を出力する
.PHONY: RunTmpEntryTargetMain
RunTmpEntryTargetMain: $(OBJECTS) ./test/tmp_entry/tmpentry.cpp
	@echo -e ${MSG_B}Compile DONE.${MSG_E}
	@echo -e ${MSG_B}Linking Unit-Test Executable.${MSG_E}
	$(CXX) $(CFLAGS) $(DEPENDENCIES_INCDIR)  -o $(RUN_TMP_ENTRY_EXEC_FILE) $^ $(DEPENDENCIES_LIBDIR) $(DEPENDENCIES_LIBS)

# src 内のビルド（cpp → object）定義
$(OBJROOT)/%.o : $(SRCROOT)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(CFLAGS) $(DEPENDENCIES_INCDIR) -o $@ -c $<

# test 内のビルド（cpp → object）定義
$(TEST_OBJROOT)/%.o : $(TEST_SRCROOT)/%.cpp
	@if [ ! -e `dirname $@` ]; then mkdir -p `dirname $@`; fi
	$(CXX) $(TEST_CLAGS) $(DEPENDENCIES_TEST_INCDIR) -o $@ -c $<


publish: $(PUBLISH_TARGET)
	@echo -e ${MSG_B}Publish DONE.${MSG_E}

.PHONY: clean_publish
clean_publish:
	@echo -e ${MSG_B}Clean publish contents.${MSG_E}
	-rm -rf ./publish/libs ./publish/includes
	@echo -e ${MSG_B}DONE.${MSG_E}


test: $(TEST_TARGET) clean_test copy_resources
	@echo -e ${MSG_B}Exec Test${MSG_E}
	$(TEST_TARGET)
	@echo -e ${MSG_B}DONE.${MSG_E}

test-%: $(TEST_TARGET) clean_test copy_resources
	@echo -e ${MSG_B}Exec Test.${MSG_E}
	$(TEST_TARGET)  --gtest_filter=${@:test-%=%}*
	@echo -e ${MSG_B}DONE.${MSG_E}

testtmp: $(RUN_TMP_ENTRY_EXEC_FILE) clean_test copy_resources
	@echo -e ${MSG_B}Exec Temp Test.${MSG_E}
	$(RUN_TMP_ENTRY_EXEC_FILE)
	@echo -e ${MSG_B}DONE.${MSG_E}

.PHONY: clean_test
clean_test:
	@echo -e ${MSG_B}Clear Debug Objects like BMP,TXT,BIN, etc..${MSG_E}
	-rm -f ./debug/*.bmp ./debug/*.txt ./debug/*.bin
	-rm -rf ./debug/resources
	@echo -e ${MSG_B}DONE.${MSG_E}


.PHONY: clean_objects
clean_objects:
	@echo -e ${MSG_B}Clear c++ compiled objects files BEGIN.${MSG_E}
	-rm -rf ./tmp/compile/src/* ./tmp/compile/test/*
	@echo -e ${MSG_B}DONE.${MSG_E}


.PHONY: clean
clean: clean_publish clean_test clean_objects
	@echo -e ${MSG_B}Clear All Test Files, Objects Files, Temp Files, DONE.${MSG_E}

.PHONY: copy_resources
copy_resources:
	@echo -e ${MSG_B}Copy Resources to Debug Directory BEGIN.${MSG_E}
	cp -f -r ./resources ./debug/
	@echo -e ${MSG_B}DONE.${MSG_E}

-include $(DEPENDS)
-include $(TEST_DEPENDS)
