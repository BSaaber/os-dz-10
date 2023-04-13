#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

int bit_arr[32];

int commit;

void *commit_handler(int nsig) {
    commit = 1;
}

int main() {
    (void)signal(SIGUSR1, commit_handler);
    printf("Hello! I am sender. My pid is: %d\n", getpid());
    printf("Enter receiver pid and number to send\n");
    pid_t receiver_pid;
    int number_to_send;
    scanf("%d %d", &receiver_pid, &number_to_send);
    unsigned _my_awesome_number = number_to_send;
    for(int i = 0; i < 32; ++i) {
        if (_my_awesome_number & 1) {
            bit_arr[31 - i] = 1;
        }
        else {
            bit_arr[31 - i] = 0;
        }
        _my_awesome_number >>= 1;
    }
    printf("sending: %d\n", number_to_send);
    printf("sending bit by bit...\n");
    for (int i = 0; i < 32; ++i) {
        if (bit_arr[i] == 1) {
            commit = 0;
            while (!commit) {
                kill(receiver_pid, SIGUSR1);
                usleep(100);
            }
            printf("1");
        }
        else {
            commit = 0;
            while (!commit) {
                kill(receiver_pid, SIGUSR2);
                usleep(100);
            }
            printf("0");
        }
    }
    printf("\n");
    usleep(100);
    kill(receiver_pid, SIGKILL);
    return 0;
}
