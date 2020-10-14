#!/bin/bash

find /home/wiktor/Desktop -iname "*.$1" -mtime -$2 > pliki
tar -cvf $3.tar.gz -T pliki 