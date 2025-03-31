gcc utils/complex_construction.c -Iutils -c -o complex_construction.o
gcc utils/console_utils.c -Iutils -c -o console_utils.o
gcc utils/doubly_linked_int_list.c -Iutils -c -o doubly_linked_int_list.o
gcc utils/singly_linked_int_list.c -Iutils -c -o singly_linked_int_list.o

gcc --shared console_utils.o complex_construction.o doubly_linked_int_list.o singly_linked_int_list.o -o libMyDynamic.so

# -Wl - вызов линковщика, -rpath - путь где искать библиотеку, он вшит в исполняемый файл, '.' - искать в текущем каталоге
gcc main.c -Iutils -o exec_file -L. -lMyDynamic -Wl,-rpath,.
./exec_file

# ----Remove files .o----
rm complex_construction.o
rm console_utils.o
rm doubly_linked_int_list.o
rm singly_linked_int_list.o
# -----------------------