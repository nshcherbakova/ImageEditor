#!/bin/bash

DEST_SERVER="192.168.86.176:8081"
DOCKER_PORT="8081"

echo "Build docker"

cd ../
docker build -f Dockerfile.txt . -t image-server

echo "Run ImageServer in docker in the address "$DEST_SERVER

docker run --rm -p $DEST_SERVER:$DOCKER_PORT --name image-server image-server
