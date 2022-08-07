#!/bin/bash

# git submodule sync
# git submodule update --init

git submodule sync && git submodule update --init && git submodule update --remote --recursive --force
