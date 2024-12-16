#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

void printAndWriteToFile(int fd, char *msg) {
    if (write(fd, msg, strlen(msg)) == -1) {
        perror("Erreur écriture fils 1");
        return;
    }
    printf("%s", msg);
}

int main (void) {
    pid_t pid_fils1, pid_fils2;
    int fd;

    char *fils1_msg = "001\n";
    char *fils2_msg ="002\n";
    char *parent_msg = "000\n";

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0640);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(0);
    }

    printAndWriteToFile(fd, parent_msg); // parent

    pid_fils1 = fork(); // creation du premier fils 1
    if (pid_fils1 == 0) {
        /* dans le fils 1 */
        printAndWriteToFile(fd, fils1_msg);
        return 0;
    } 

    pid_fils2 = fork(); // creation du deuxieme fils 2
    if (pid_fils2 == 0) {
        /* dans le fils 2 */
        printAndWriteToFile(fd, fils2_msg);
        return 0;
    }

    return 0;
}
