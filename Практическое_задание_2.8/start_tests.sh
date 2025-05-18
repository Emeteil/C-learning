mkdir Build
cd Build
cmake ../tests
make
ctest -V --output-on-failure