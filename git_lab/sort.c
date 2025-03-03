void _swap(Student *a, Student *b) {
    Student tmp = *a;
    *a = *b;
    *b = tmp;
}

// new comment
// second comment

// O(n^2)
void insertionSort(Student list[], size_t N, int (*func)(Student, Student)) {
    for (int i = 1; i < N; i++) {
        for (int j = i; j > 0; j--) {
            if (func(list[j], list[j - 1])) break;

            _swap(&list[j], &list[j - 1]);
        }
    }
}
