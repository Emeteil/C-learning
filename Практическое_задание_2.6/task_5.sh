mkdir -p Build;
cd Build;

LIB_TYPE="${1:-STATIC}"

cmake -DLIB_TYPE="$LIB_TYPE" ..;
cmake --build .;
./a.out;