FROM ubuntu:latest

RUN apt-get update \
    && apt-get install -y git \
                          g++ \
                          cmake \
                          wget

RUN cd /home/ && wget https://boostorg.jfrog.io/artifactory/main/release/1.81.0/source/boost_1_81_0.tar.gz

RUN cd /home/ && tar -xzvf boost_1_81_0.tar.gz \
    && rm boost_1_81_0.tar.gz \
    && cd boost_1_81_0 \
    && ./bootstrap.sh --prefix=/usr/local \
    && ./b2 install \
    && cd /home/ \
    && rm -rf boost_1_81_0

ADD ./../ /csm
WORKDIR /csm

RUN cmake -B "serverBuild" -S "server" \
    && cd serverBuild \
    && make \
    && ./startServer