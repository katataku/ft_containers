FROM debian:stable-slim

WORKDIR /app

RUN apt-get update && apt-get install -y \
	cmake \
	make \
	gcc \
	googletest \
	g++ \
	python3-pip \
	valgrind \
	clang-format \
	clang-tidy \
	git

# GoogleTestsのインストール
# REF: https://stackoverflow.com/questions/24295876/cmake-cannot-find-googletest-required-library-in-ubuntu
RUN (cd /usr/src/googletest && cmake . && cmake --build . --target install)

# cpplintのインストール
RUN pip install cpplint

# prevent container from terminating
# GoogleBenchのインストール
# Ref: https://github.com/google/benchmark#requirements

RUN (cd /usr/src &&\
	git clone https://github.com/google/benchmark.git &&\
	cd benchmark &&\
	cmake -E make_directory "build" &&\
	cmake -E chdir "build" cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=on -DCMAKE_BUILD_TYPE=Release ../ &&\
	cmake --build "build" --config Release --target install)

ENTRYPOINT ["tail", "-f", "/dev/null"]
