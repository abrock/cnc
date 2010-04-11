#!/bin/bash

g++ drehbank2.cpp
cat head > dreh.svg
./a.exe >> dreh.svg
echo "</svg>" >> dreh.svg
