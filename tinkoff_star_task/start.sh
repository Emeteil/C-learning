gcc start_task_1.c -lm;

echo "Тестируем программу с аргументами: 1-10,13-15,55,66,88-99,106";
./a.out 1-10,13-15,55,66,88-99,106;

echo "Тестируем программу с аргументами: 1,3,5,7,9,11,13,15,17,19,21";
./a.out 1,3,5,7,9,11,13,15,17,19,21;

echo "Тестируем программу с аргументами: 2-4,6-8,10-12,14-16,18-20";
./a.out 2-4,6-8,10-12,14-16,18-20;

echo "Тестируем программу с аргументами: 100-110,120-130,140-150";
./a.out 100-110,120-130,140-150;

echo "Тестируем программу с аргументами: 5,10,15,20,25,30,35,40,45,50";
./a.out 5,10,15,20,25,30,35,40,45,50;

echo "Тестируем программу с аргументами: 1-5,10-15,20-25,30-35,40-45,50-55";
./a.out 1-5,10-15,20-25,30-35,40-45,50-55;