mkdir -p Build
cd Build
cmake ..
make
ctest -V --output-on-failure
