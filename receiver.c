#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

unsigned _my_awesome_number = 0;
int counter = 0;
pid_t sender_pid = -1;
int byte_arr[32];

int check_for_end() {
    if (counter == 32) {
        for (int i = 0; i < 32; ++i) {
            printf("%d", byte_arr[i]);
        }
        int answer = (int) _my_awesome_number;
        printf("\nanswer: %d\n", answer);
        return 1;
    }
    return 0;
}

void *zero_bit_handler(int nsig) {
    if (sender_pid != -1) {
        _my_awesome_number |= 1;
        byte_arr[counter++] = 1;
        kill(sender_pid, SIGUSR1);
        if (check_for_end() == 0) {
            _my_awesome_number <<= 1;
        }
    }
}

void *one_bit_handler(int nsig) {
    if (sender_pid != -1) {
        byte_arr[counter++] = 0;
        kill(sender_pid, SIGUSR1);
        if (check_for_end() == 0) {
            _my_awesome_number <<= 1;
        }
    }
}

int main() {
    (void)signal(SIGUSR1, zero_bit_handler);
    (void)signal(SIGUSR2, one_bit_handler);
    printf("Hello! I am receiver. My pid is: %d\n", getpid());
    printf("Enter sender pid\n");
    scanf("%d", &sender_pid);



    int nothing;
    while (1);
    return 0;
}
