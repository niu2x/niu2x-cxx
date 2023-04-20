#!/bin/bash

# ./bootstrap.sh
# ./b2

find ../external_boost/boost -type f|grep -v "\.hpp"|while read item; do rm "$item"; done