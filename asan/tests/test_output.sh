#!/bin/bash

OS=`uname`
CXX=../../clang_build_$OS/Release+Asserts/bin/clang++
SYMBOLIZER=../../scripts/asan_symbolize.py

for t in  *.tmpl; do
  for b in 32 64; do
    for O in 0 1 2 3; do
      c=`basename $t .tmpl`
      c_so=$c-so
      exe=$c.$b.O$O
      so=$c_so.$b.O$O.so
      $CXX -g -m$b -fasan -O$O $c.cc -o $exe
      [ -e "$c_so.cc" ] && $CXX -g -m$b -fasan -O$O $c_so.cc -fPIC -shared -o $so
      ./$exe 2>&1 | $SYMBOLIZER 2> /dev/null | c++filt | ./match_output.py $t || exit 1
      echo $exe
      rm ./$exe
      [ -e "$so" ] && rm ./$so
    done
  done
done
exit 0
