mkdir bin
cd src
g++ --std=c++14 *.cpp -o ../bin/benchmark -O0 -mavx -msse2 -D BENCHMARKS
cd ../
cd bin
cmd /k benchmark.exe