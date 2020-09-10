#!/bin/bash
OCWD=$PWD
cd "$(dirname "$0")"
./block-fight &
cd $OCWD
OCWD=""

