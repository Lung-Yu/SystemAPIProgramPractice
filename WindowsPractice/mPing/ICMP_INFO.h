#include <stdio.h>
#include <winsock2.h>

#pragma comment (lib, "ws2_32")

typedef struct icmp_header
{
	unsigned char  type;
	unsigned char  code;
	unsigned short checksum;
	unsigned short id;
	unsigned short sequence;
	unsigned long  timestamp;
}ICMP_HEADER;

#define ICMP_HEADER_SIZE sizeof(ICMP_HEADER)
#define ICMP_ECHO_REQUEST 0x08
#define ICMP_ECHO_REPLY 0x00

unsigned short chsum(ICMP_HEADER *picmp, int len);
BOOL mPing(char *szDestIp);