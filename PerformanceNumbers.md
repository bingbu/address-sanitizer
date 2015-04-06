# Spec CPU 2006 (C/C++) #

These numbers are measured on [SPEC 2006](RunningSpecBenchmarks.md) (C/C++ only) using Clang3.3 (trunk) [r179094](https://code.google.com/p/address-sanitizer/source/detail?r=179094) (April 09 2013) on Intel Xeon W3690 @3.47GHz. 

&lt;BR&gt;


2-nd column: `clang -O2` 

&lt;BR&gt;


3-rd column: `clang -O2 -fsanitize=address -fno-omit-frame-pointer`
| BENCHMARK            |  O2       | O2+asan | slowdown|
|:---------------------|:----------|:--------|:--------|
|       400.perlbench|      344.00|     1304.00|        3.79|
|           401.bzip2|      490.00|      844.00|        1.72|
|             403.gcc|      322.00|      608.00|        1.89|
|             429.mcf|      316.00|      583.00|        1.84|
|           445.gobmk|      409.00|      833.00|        2.04|
|           456.hmmer|      605.00|     1226.00|        2.03|
|           458.sjeng|      456.00|      982.00|        2.15|
|      462.libquantum|      480.00|      539.00|        1.12|
|         464.h264ref|      547.00|     1311.00|        2.40|
|         471.omnetpp|      314.00|      587.00|        1.87|
|           473.astar|      403.00|      655.00|        1.63|
|       483.xalancbmk|      227.00|      493.00|        2.17|
|            433.milc|      408.00|      666.00|        1.63|
|            444.namd|      369.00|      593.00|        1.61|
|          447.dealII|      321.00|      597.00|        1.86|
|          450.soplex|      233.00|      367.00|        1.58|
|          453.povray|      189.00|      425.00|        2.25|
|             470.lbm|      318.00|      393.00|        1.24|
|         482.sphinx3|      519.00|      911.00|        1.76|

The average slowdown is **1.93**, the median slowdown is **1.86**.

Older measurements: asan [r496](https://code.google.com/p/address-sanitizer/source/detail?r=496) (`clang -O2 -fsanitize=address`) with `malloc_context_size=1` (i.e. no unwinding).

&lt;BR&gt;


The baseline is `clang -O2`. 

&lt;BR&gt;


The average slowdown introduced by full instrumentation (red) is **1.73**.

&lt;BR&gt;


When only writes are instrumented (blue), the average slowdown is **1.26**.

![http://address-sanitizer.googlecode.com/svn/trunk/img/spec_r496.png](http://address-sanitizer.googlecode.com/svn/trunk/img/spec_r496.png)