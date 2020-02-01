#include "ICMP_INFO.h"

int main(int argc, char **argv)
{
	for (int i = 0; i < 100; i++){
		mPing("8.8.8.8");
		Sleep(500);
	}

	return 0;
}

unsigned short chsum(ICMP_HEADER *picmp, int len)
{
	long sum = 0;
	unsigned short *pusicmp = (unsigned short *)picmp;

	while (len > 1)
	{
		sum += *(pusicmp++);
		if (sum & 0x80000000)
			sum = (sum & 0xffff) + (sum >> 16);
		len -= 2;
	}

	if (len)
		sum += (unsigned short)*(unsigned char *)pusicmp;

	while (sum >> 16)
		sum = (sum & 0xffff) + (sum >> 16);

	return (unsigned short)~sum;
}

BOOL mPing(char *szDestIp)
{	
	BOOL bRet = TRUE;
	WSADATA wsaData;
	int nTimeOut = 1000;
	char szBuff[ICMP_HEADER_SIZE + 32] = { 0 };
	icmp_header *pIcmp = (icmp_header *)szBuff;
	char icmp_data[32] = { 0 };

	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET s = socket(PF_INET, SOCK_RAW, IPPROTO_ICMP);

	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char const*)&nTimeOut, sizeof(nTimeOut));

	sockaddr_in dest_addr;
	dest_addr.sin_family = AF_INET;
	dest_addr.sin_addr.S_un.S_addr = inet_addr(szDestIp);
	dest_addr.sin_port = htons(0);

	pIcmp->type = ICMP_ECHO_REQUEST;
	pIcmp->code = 0;
	pIcmp->id = (USHORT)::GetCurrentProcessId();
	pIcmp->sequence = 0;
	pIcmp->timestamp = 0;
	pIcmp->checksum = 0;

	memcpy((szBuff + ICMP_HEADER_SIZE), "abcdefghijklmnopqrstuvwabcdefghi", 32);

	pIcmp->checksum = chsum((ICMP_HEADER *)szBuff, sizeof(szBuff));

	sockaddr_in from_addr;
	char szRecvBuff[1024];
	int nLen = sizeof(from_addr);
	sendto(s, szBuff, sizeof(szBuff), 0, (SOCKADDR *)&dest_addr, sizeof(SOCKADDR));
	recvfrom(s, szRecvBuff, MAXBYTE, 0, (SOCKADDR *)&from_addr, &nLen);

	if (lstrcmp((LPCWSTR)inet_ntoa(from_addr.sin_addr), (LPCWSTR)szDestIp))
	{
		bRet = FALSE;
	}
	else
	{
		struct icmp_header *pIcmp1 = (icmp_header *)(szRecvBuff + 20);
		printf("%s\r\n", inet_ntoa(from_addr.sin_addr));
	}
	return bRet;
}

