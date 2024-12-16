#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main (void) {
    pid_t pid_fils1, pid_fils2;

    printf("000\n"); // parent

    pid_fils1 = fork(); // creation du premier fils 1
    if (pid_fils1 == 0) {
        /* dans le fils 1 */
        printf("001\n");
        return 0;
    } 

    pid_fils2 = fork(); // creation du deuxieme fils 2
    if (pid_fils2 == 0) {
        /* dans le fils 2 */
        printf("002\n");
        return 0;
    }

    return 0;
}