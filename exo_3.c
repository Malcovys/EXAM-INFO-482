#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main() {
    pid_t p_fils;
    int fd;

    fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0640);
    if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(0);
    }

    p_fils = fork();
    if (p_fils == -1) {
        perror("Erreur lors de la création du processus");
        close(fd);
        exit(0);
    }

    if (p_fils == 0) {
        // Enfant
        if (dup2(fd, STDOUT_FILENO) == -1) { // redirige la sortie standard vers le fichier
            perror("Erreur lors de la redirection de la sortie standard");
            close(fd);
            exit(0);
        }
        close(fd);
        // Pour pourvoir être rediriger
        execlp("ps", "ps", "-e", NULL);

        perror("Erreur lors de l'exécution de la commande ps");
        exit(0);
    } else {
        // processus parent
        wait(NULL); //  attendre la fin du processus enfant
        close(fd);

        // Afficher la liste des processus à l'écran
        system("ps -e");
    }

    return 0;
}