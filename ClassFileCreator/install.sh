#!/bin/bash
c++ -Wall -Wextra -Werror main.cpp -o hpp
mkdir ~/.bin 2>/dev/null
mv hpp ~/.bin
