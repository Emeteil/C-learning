/*
 * Классическая задача с обедающими философами и дедлоком
 * Без стыда украл исходник из НГУ POSIX практикума
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define PHILO 5
#define DELAY 30000
#define FOOD 50

pthread_mutex_t forks[PHILO];
pthread_t phils[PHILO];
void *philosopher(void *id);
int food_on_table();
void get_fork(int, int, char *);
void down_forks(int, int);
pthread_mutex_t foodlock;

int sleep_seconds = 0;

int main(int argn, char **argv) {
    int i;
  
    if (argn == 2)
        sleep_seconds = atoi(argv[1]);
  
    pthread_mutex_init(&foodlock, NULL);
    for (i = 0; i < PHILO; i++)
        pthread_mutex_init(&forks[i], NULL);
    for (i = 0; i < PHILO; i++)
        pthread_create(&phils[i], NULL, philosopher, (void *)i);
    for (i = 0; i < PHILO; i++)
        pthread_join(phils[i], NULL);
    return 0;
}

void *philosopher(void *num) {
    int id;
    int left_fork, right_fork, f;
  
    id = (int)num;
    printf("Philosopher %d sitting down to dinner.\n", id);
    right_fork = id;
    left_fork = id + 1;
  
    /* Wrap around the forks. */
    if (left_fork == PHILO)
        left_fork = 0;

    // ------------------------------------------------------------
    /* Меняем порядок взятия вилок у последнего философа.
    Все философы юерут вилку С НАИМЕНЬШИМ НОМЕРОМ, что
    помогает избежать deadlock */
    // https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE%D0%B1_%D0%BE%D0%B1%D0%B5%D0%B4%D0%B0%D1%8E%D1%89%D0%B8%D1%85_%D1%84%D0%B8%D0%BB%D0%BE%D1%81%D0%BE%D1%84%D0%B0%D1%85#%D0%98%D0%B5%D1%80%D0%B0%D1%80%D1%85%D0%B8%D1%8F_%D1%80%D0%B5%D1%81%D1%83%D1%80%D1%81%D0%BE%D0%B2:~:text=%D0%B2%D1%81%D0%B5%D0%B3%D0%B4%D0%B0%20%D0%B1%D0%B5%D1%80%D1%91%D1%82%20%D1%81%D0%BD%D0%B0%D1%87%D0%B0%D0%BB%D0%B0%20%D0%B2%D0%B8%D0%BB%D0%BA%D1%83%20%D1%81%20%D0%BD%D0%B0%D0%B8%D0%BC%D0%B5%D0%BD%D1%8C%D1%88%D0%B8%D0%BC%20%D0%BD%D0%BE%D0%BC%D0%B5%D1%80%D0%BE%D0%BC
    if (id == PHILO - 1) {
        int tmp = left_fork;
        left_fork = right_fork;
        right_fork = tmp;
    }
    /* Также есть вариант добавления "официанта" в задачу, который
    будет разрешать брать вилку философу, на ru wiki советуют взять
    в качесте "официанта" семафор */
    // ------------------------------------------------------------
  
    while (f = food_on_table()) {
        /* Thanks to philosophers #1 who would like to
         * take a nap before picking up the forks, the other
         * philosophers may be able to eat their dishes and
         * not deadlock.
         */
    
        if (id == 1)
            sleep(sleep_seconds);
    
        printf("Philosopher %d: get dish %d.\n", id, f);
        get_fork(id, right_fork, "right");
        get_fork(id, left_fork, "left ");
    
        printf("Philosopher %d: eating.\n", id);
        usleep(DELAY * (FOOD - f + 1));
        down_forks(left_fork, right_fork);
    }
    printf("Philosopher %d is done eating.\n", id);
    return (NULL);
}

int food_on_table() {
    static int food = FOOD;
    int myfood;
  
    pthread_mutex_lock(&foodlock);
    if (food > 0) {
        food--;
    }
    myfood = food;
    pthread_mutex_unlock(&foodlock);
    return myfood;
}

void get_fork(int phil, int fork, char *hand) {
    pthread_mutex_lock(&forks[fork]);
    printf("Philosopher %d: got %s fork %d\n", phil, hand, fork);
}

void down_forks(int f1, int f2) {
    pthread_mutex_unlock(&forks[f1]);
    pthread_mutex_unlock(&forks[f2]);
}
