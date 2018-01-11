//
//	作者：齊藤芳紀
//
//	内容：WinSockを使いやすくラップした
//		：受信したデータを保存しておいて、後でもらえるようにした
//


#pragma once

#include <winsock2.h>
#include <cassert>

#include <thread>
#include <mutex>
#include <deque>
#include <memory>
#include <string>
#include <vector>

#pragma	comment(lib,"ws2_32.lib")
#pragma warning(disable: 4996)


class WinSockError {
public:

	//エラーコードを、エラーメッセージに変換する
	static const char* GetErrorMessage(int aErrorCode) {

		switch (aErrorCode) {
			case WSAENETDOWN:
				return "The Windows Sockets implementation has detected that the network subsystem has failed.";
			case WSAENOTCONN:
				return "The socket is not connected.";
			case WSAEINTR:
				return "The (blocking) call was canceled using WSACancelBlockingCall.";
			case WSAEINPROGRESS:
				return "A blocking Windows Sockets operation is in progress.";
			case WSAENOTSOCK:
				return "Th4e descriptor is not a socket.";
			case WSAEOPNOTSUPP:
				return "MSG_OOB was specified, but the socket is not of type SOCK_STREAM.";
			case WSAESHUTDOWN:
				return "The socket has been shut down; it is not possible to recv on a socket"
				" after shutdown has been invoked with how set to 0 or 2.";
			case WSAEWOULDBLOCK:
				return "The socket is marked as nonblocking and the receive operation would block.";
			case WSAEINVAL:
				return "The socket has not been bound with bind.";
			case WSANOTINITIALISED:
				return "A successful WSAStartup must occur before using this function.";
			case WSAEAFNOSUPPORT:
				return "The specified address family is not supported.";
			case WSAEMFILE:
				return "No more file descriptors are available.";
			case WSAENOBUFS:
				return "No buffer space is available. The socket cannot be created.";
			case WSAEPROTONOSUPPORT:
				return "The specified protocol is not supported.";
			case WSAEPROTOTYPE:
				return "The specified protocol is the wrong type for this socket.";
			case WSAESOCKTNOSUPPORT:
				return "The specified socket type is not supported in this address family.";
			case WSAEADDRINUSE:
				return "The specified address is already in use. (See the SO_REUSEADDR"
				" socket option under setsockopt.)";
			case WSAEFAULT:
				return "The namelen argument is too small (less than the size of a struct sockaddr).";
			case WSAEADDRNOTAVAIL:
				return "The specified address is not available from the local computer.";
			case WSAECONNREFUSED:
				return "The attempt to connect was forcefully rejected.";
			case WSAEDESTADDRREQ:
				return "A destination address is required.";
			case WSAEISCONN:
				return "The socket is already connected.";
			case WSAENETUNREACH:
				return "The network can't be reached from this host at this time.";
			case WSAETIMEDOUT:
				return "Attempt to connect timed out without establishing a connection";
			case WSAECONNRESET:
				return "The connection was reset by the remote side.";
			case WSAEACCES:
				return "The requested address is a broadcast address, but the appropriate flag was not set.";
			case WSAENETRESET:
				return "The connection must be reset because the Windows Sockets implementation dropped it.";
			case WSAEMSGSIZE:
				return "The socket is of type SOCK_DGRAM, and the datagram is larger "
				"than the maximum supported by the Windows Sockets implementation.";
			case WSAECONNABORTED:
				return "The virtual circuit was aborted due to timeout or other failure.";

			default:
				return "This ErrorCode Has No Message";
		}
	
	}
};

#define SAITO_WINSOCK_ERROR(ErrorMessage) ::MessageBoxA(NULL, ErrorMessage, "WINSOCK ERROR !!", MB_OK);


struct NetworkConnectData {
public:
	NetworkConnectData() {
		addr.sin_family = PF_INET;

		const unsigned int cDefaultPort = 30000;
		const char* cDefaultAddress = "127.0.0.1";

		SetPortNo(cDefaultPort);
		SetAddress(cDefaultAddress);
	}

	bool operator ==(const NetworkConnectData& aOther) const {
		if (addr.sin_port != aOther.addr.sin_port) return false;
		if (addr.sin_addr.S_un.S_addr != aOther.addr.sin_addr.S_un.S_addr) return false;
		return true;
	}
	bool operator !=(const NetworkConnectData& aOther) const {
		return !(*this == aOther);
	}

public:
	void SetPortNo(unsigned short port) {
		addr.sin_port = htons(port);
	}
	unsigned short GetPortNo() const {
		return ntohs(addr.sin_port);
	}
	void SetAddress(const char* address) {
		addr.sin_addr.S_un.S_addr = inet_addr(address);
	}
	void SetAddress(ULONG address) {
		addr.sin_addr.S_un.S_addr = address;
	}

public:
	sockaddr_in addr;
};




template <typename T>
struct NetworkMessageData {
	NetworkConnectData connectData;
	std::unique_ptr<T> data;
};


template <typename T>
class NetworkDataList {
public:
	std::shared_ptr<NetworkMessageData<T>> PopData() {
		if (MessageDataNum() != 0) {
			std::shared_ptr<NetworkMessageData<T>> d = *(dataList.begin());
			dataList.pop_front();
			return d;
		}
		else {
			return std::shared_ptr<NetworkMessageData<T>>();
		}
	}
	void PushData(std::shared_ptr<NetworkMessageData<T>> aData) {
		dataList.push_back(aData);
	}
	int MessageDataNum() {
		return dataList.size();
	}
	
private:
	std::deque<std::shared_ptr<NetworkMessageData<T>>> dataList;
};


class WinSock {
private:
	WinSock() {
		errorCode = 0;
	}
	WinSock(const WinSock&) = delete;
	const WinSock& operator =(const WinSock&) = delete;
public:
	static WinSock& S() {
		static WinSock s;
		return s;
	}

public:
	bool Initialize() {

		WSADATA		wd;
		WORD wsa_version = MAKEWORD(2, 2);
		int sts = 0;

		sts = WSAStartup(wsa_version, &wd);

		if (sts == SOCKET_ERROR) {
			errorCode = WSAGetLastError();
			return false;
		}

		if (wsa_version != wd.wVersion) {
			return false;
		}
		return true;
	}
	bool Finalize() {
		int sts = WSACleanup();

		if (sts == SOCKET_ERROR) {
			errorCode = WSAGetLastError();
			return false;
		}

		return true;
	}

	const char* GetLastError() {
		return WinSockError::GetErrorMessage(errorCode);
	}

	int errorCode;
};


template <typename T>
class Network {
public:
	Network() {
		isInit = false;
		isReceive = false;
		isThreadRunning = false;
	}
	~Network() {
		Final();
	}

	bool Init() {
		socket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_IP);
		if (socket == INVALID_SOCKET) {
			SetErrorCode(WSAGetLastError());
			return false;
		}
		isInit = true;
		return true;
	}
	void Final() {
		if (isInit) {
			Join();
			if (socket != INVALID_SOCKET) {
				closesocket(socket);
			}
			isInit = false;
		}
	}


	bool SetBroadCast(bool isBroadcast) {

		bool flg = isBroadcast;
		int res = setsockopt(socket, SOL_SOCKET, SO_BROADCAST, (const char*)&flg, sizeof(bool));
		if (res == SOCKET_ERROR) {
			SetErrorCode(WSAGetLastError());
			return false;
		}
		return true;
	}

	bool SetBufferSize(int aNewBufferSize) {
		int res = setsockopt(socket, SOL_SOCKET, SO_RCVBUF, (const char *)&aNewBufferSize, sizeof(int));
		if (res == SOCKET_ERROR) {
			SetErrorCode(WSAGetLastError());
			return false;
		}
		return true;
	}

	bool SetReceiveBlocking(bool aBlocking) {
		u_long tBlockMode = aBlocking ? 0 : 1;	//ブロッキングするときは0で、それ以外ならノンブロッキングになる
		int res = ioctlsocket(socket, FIONBIO, &tBlockMode);
		if (res == SOCKET_ERROR) {
			SetErrorCode(WSAGetLastError());
			return false;
		}
		return true;
	}

	template <typename U>
	bool Send(const NetworkConnectData& aConnectData, const U& aData) {

		int sts = sendto(socket, (const char*)(&aData), sizeof(U), 0, (sockaddr*)&(aConnectData.addr), sizeof(sockaddr));
		if (sts == SOCKET_ERROR) {
			SetErrorCode(WSAGetLastError());
			return false;
		}

		return true;
	}

	bool Bind(unsigned short aPortNo) {
		sockaddr_in addr;
		addr.sin_family = AF_INET;
		addr.sin_port = htons(aPortNo);
		addr.sin_addr.S_un.S_addr = INADDR_ANY;
		int res = bind(socket, (sockaddr*)&addr, sizeof(sockaddr_in));
		if (res == SOCKET_ERROR) {
			SetErrorCode(WSAGetLastError());
			return false;
		}
		return true;
	}

	void StartReceive() {
		if (GetIsThreadRunning()) {
			return;
		}
		SetIsReceive(true);
		recvThread = std::thread(&Network<T>::ReceiveThread, this);
	}
	void StopReceive() {
		SetIsReceive(false);
	}

	void ReceiveThread() {
		SetIsThreadRunning(true);

		int fromlen = sizeof(sockaddr_in);

		//受信のループ
		while (true) {

			//
			//受信
			//
			std::unique_ptr<T> tData(new T);	//受信用バッファ
			sockaddr_in fromaddr;

			//パケットを取得できるまで繰り返す（ノンブロッキングの為）
			while (true) {
				
				//レシーブ処理を終了する必要があるなら
				if (GetIsReceive() == false) {
					//スレッドを停止する
					SetIsThreadRunning(false);
					return;
				}

				//パケットの受信
				int res = recvfrom(socket, (char*)(&(*tData)), sizeof(T), 0, (sockaddr*)&fromaddr, &fromlen);

				//パケットの受信でエラーが起きたら
				if (res == SOCKET_ERROR) {
					SetErrorCode(WSAGetLastError());
					
					if (GetErrorCode() == WSAEWOULDBLOCK) {
						continue;	//ノンブロッキングでデータがない場合はこのエラーが出るので、無視する
					}
					SAITO_WINSOCK_ERROR(GetLastError());
				}

				//もしパケットを取得できていたら
				if (res == sizeof(T)) {
					break;	//このwhileループを抜け、データの格納作業へ
				}
			}
			


			//データの格納
			{
				//データの作成
				std::shared_ptr<NetworkMessageData<T>> messageData = std::make_shared<NetworkMessageData<T>>();
				(*messageData).connectData.addr = fromaddr;
				(*messageData).data = std::move(tData);

				std::lock_guard<std::mutex> l(dataListMutex);
				dataList.PushData(messageData);
			}
		}
	}
	void Join() {
		if (GetIsThreadRunning()) {
			SetIsReceive(false);
			if (recvThread.joinable()) {
				recvThread.join();
			}
		}
	}

	std::shared_ptr<NetworkMessageData<T>> ReceiveData() {
		std::lock_guard<std::mutex> l(dataListMutex);
		return dataList.PopData();
	}
	void ReverseData(std::shared_ptr<NetworkMessageData<T>> data) {
		std::lock_guard<std::mutex> l(dataListMutex);
		dataList.PushData(data);
	}


	bool ExistData() {
		std::lock_guard<std::mutex> l(dataListMutex);
		return dataList.MessageDataNum() != 0;
	}

	const char* GetLastError() {
		return WinSockError::GetErrorMessage(GetErrorCode());
	}

private:
	SOCKET socket;
	bool isInit;

	std::mutex errorCodeMutex;
	int errorCode;
	int GetErrorCode() {
		std::lock_guard<std::mutex> l(errorCodeMutex);
		return errorCode;
	}
	void SetErrorCode(int aErrorCode) {
		std::lock_guard<std::mutex> l(errorCodeMutex);
		errorCode = aErrorCode;
	}

	std::mutex isReceiveMutex;
	bool isReceive;
	bool GetIsReceive() {
		std::lock_guard<std::mutex> l(isReceiveMutex);
		return isReceive;
	}
	void SetIsReceive(bool aIsReceive) {
		std::lock_guard<std::mutex> l(isReceiveMutex);
		isReceive = aIsReceive;
	}

	std::mutex isThreadRunningMutex;
	bool isThreadRunning;
	bool GetIsThreadRunning() {
		std::lock_guard<std::mutex> l(isThreadRunningMutex);
		return isThreadRunning;
	}
	void SetIsThreadRunning(bool aIsThreadRunning) {
		std::lock_guard<std::mutex> l(isThreadRunningMutex);
		isThreadRunning = aIsThreadRunning;
	}

	std::thread recvThread;

	std::mutex dataListMutex;
	NetworkDataList<T> dataList;
};