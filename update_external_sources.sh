#!/bin/bash

# git submodule sync
# git submodule update --init

git pull --recurse-submodules && git submodule update --remote --recursive
