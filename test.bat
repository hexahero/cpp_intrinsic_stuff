mkdir bin
cd src
g++ --std=c++14 *.cpp -o ../bin/test -mavx -msse2 -D TESTS
cd ../
cd bin
cmd /k test.exe