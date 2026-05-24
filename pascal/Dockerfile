FROM --platform=linux/386 debian:bookworm-slim

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ca-certificates \
        fpc \
        make \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /pascal

COPY Makefile /pascal/Makefile
COPY struct_abi.pas /pascal/struct_abi.pas

RUN make
