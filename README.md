# GS 에디터

## 미리보기

(WIP)

## 작업 환경

### 환경

* 윈도우10 이상
* msys2 (mingw64): 환경 변수 `MSYS2_HOME`가 등록되어 있어야 VSCode에서 디버깅이 가능  
  (MSYS2_HOME: msys2가 설치된 경로)

### VSCode 확장

* `C/C++`: .clang-format, 인텔리센스, 디버그 구성,

### 빌드 설명

* `make`: 프로젝트를 빌드합니다. `build/release/bin/GSEditor.exe`가 생성됩니다.
* `make cxxsync`: 인텔리센스를 위한 `compile_commands.json`을 생성합니다.

## 프로젝트 의존성

### 빌드

* mingw-w64-x86_64-toolchain
* upx
* make

### 라이브러리

* mingw-w64-x86_64-wxwidgets3.2-msw
* mingw-w64-x86_64-utf8cpp
* xxhash
* xdelta3
* lz, lzma
* rgbds (프로세스)

## 라이선스

라이선스 없음

## 3자 라이선스 고지

* [LICENSE.txt](./LICENSE.txt)
* 프로그램 정보에서 확인 (도움말 > 프로그램 정보 > 오픈소스 라이선스)
