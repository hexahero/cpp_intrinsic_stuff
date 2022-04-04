mkdir bin
cd src
g++ --std=c++14 *.cpp -o ../bin/run -O3 -mavx -msse2 -D BUILD
cd ../
cd bin
cmd /k run.exe