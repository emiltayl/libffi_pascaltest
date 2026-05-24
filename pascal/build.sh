#!/bin/sh
docker build --platform linux/386 -t pascal-struct-abi .

cid="$(docker create pascal-struct-abi)"
docker cp "$cid:/pascal/libstruct_abi.so" ./libstruct_abi.so
docker rm "$cid"