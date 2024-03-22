FROM ubuntu:latest

WORKDIR /usr/src/app

# ? https://askubuntu.com/questions/1173337/how-to-prevent-system-from-being-minimized

RUN apt-get update && apt install tzdata -y && apt install net-tools vim man file -y
RUN yes| unminimize
RUN apt-get update -y && apt-get upgrade -y
RUN apt-get install -y vim perl wget tar man sudo adduser netstat-nat net-tools curl w3m
RUN apt-get install build-essential -y


ENV SHELL /bin/bash

COPY ./final-src-osc10e .


