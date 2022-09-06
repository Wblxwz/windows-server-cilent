#include "server.h"

int main(int argc, char* argv[])
{
	WSADATA wsadata;
	char buf[256]{ "0" };
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		std::cout << "ÍøÂç¿â¼ÓÔØÊ§°Ü" << std::endl;
		return 0;
	}
	int serverfd = socket(AF_INET, SOCK_STREAM, 0), connectfd;
	sockaddr_in server, cilent;
	if (serverfd == -1)
	{
		std::cerr << "Error server socket" << std::endl;
		exit(EXIT_FAILURE);
	}
	inet_pton(AF_INET, ip, &server.sin_addr.S_un.S_addr);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;
	int ret = bind(serverfd, (sockaddr*)&server, sizeof(server));
	if (ret == -1)
	{
		closesocket(serverfd);
		std::cerr << "Error server bind" << std::endl;
		exit(EXIT_FAILURE);
	}
	ret = listen(serverfd, 1024);
	if (ret == -1)
	{
		closesocket(serverfd);
		std::cerr << "Error server listen" << std::endl;
		exit(EXIT_FAILURE);
	}
	socklen_t len = sizeof(cilent);
	while (true)
	{
		connectfd = accept(serverfd, (sockaddr*)&cilent, &len);
		if (serverfd == -1)
		{
			std::cerr << "Error server accept" << std::endl;
			continue;
		}
		std::cout << "connect successful" << std::endl;
		while ((ret = recv(connectfd, buf, sizeof(buf), NULL)))
		{
			std::cout << inet_ntop(AF_INET, (void*)&cilent.sin_addr, buf, sizeof(buf)) << ":" << buf << std::endl;
			send(connectfd, buf, sizeof(buf), NULL);
		}
		if (ret == 0)
		{
			std::cerr << "Error recv server" << std::endl;
		}
		closesocket(connectfd);
	}
	closesocket(serverfd);
	return 0;
}