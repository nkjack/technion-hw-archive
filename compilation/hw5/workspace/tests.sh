#!/usr/bin/env bash

chmod +x *.tcl

echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~COMPI 5 TEST~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
dos2unix --quiet tests/*
dos2unix --quiet tests/prev/* 
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~RUN NEW TESTS!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
./run_tests.tcl
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~RUN PREV TESTS!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
./run_tests_prev.tcl
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~COMPI 5 TEST FINISHED~~~~~~~~~~~~~~~~~~~~~~~~~~~"


