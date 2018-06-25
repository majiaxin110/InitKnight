#ifndef __SOCKET_CLIENT_H__
#define __SOCKET_CLIENT_H__
#include "SocketBase.h"

class SocketClient : public SocketBase
{
public:
	static SocketClient* construct();
	void destroy();

	bool connectServer(const char* serverIP, unsigned short port);
	void sendMessage(const char* data, int count);//发送信息

	std::function<void(const char* data, int count)> onRecv;
	std::function<void()> onDisconnect;

	void update(float dt);//逐帧更新

CC_CONSTRUCTOR_ACCESS:
	SocketClient(void);
	~SocketClient(void);

private:
	bool initClient();
	void recvMessage();
	void clear();

private:
	HSocket _socketServer;
	HSocket _socektClient;
	std::list<SocketMessage*> _UIMessageQueue;
	std::mutex   _UIMessageQueueMutex;
};

#endif

