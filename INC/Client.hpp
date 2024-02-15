#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "Server.hpp"
#include "Channel.hpp"

class Client
{
private:
	int fd;
	bool isOperator;
	bool registered;
	std::string nickname;
	std::string username;
	std::string buffer;
	std::string ipadd;
	bool isPlaying;
	std::vector<std::string> ChannelsInvite;
public:
	Client();
	Client(std::string nickname, std::string username, int fd);
	~Client();
	Client(Client const &src);
	Client &operator=(Client const &src);
	//---------------//Getters
	int GetFd();
	bool getRegistered();
	bool GetInviteChannel(std::string &ChName);
	std::string GetNickName();
	std::string GetUserName();
	std::string getIpAdd();
	std::string getBuffer();
	std::string getHostname();
	bool 		getIsPlaying();
	//---------------//Setters
	void SetFd(int fd);
	void SetNickname(std::string& nickName);
	void SetUsername(std::string& username);
	void setBuffer(std::string recived);
	void setRegistered(bool value);
	void setIpAdd(std::string ipadd);
	void setIsPlaying(bool value);
	//---------------//Methods
	void clearBuffer();
	void AddChannelInvite(std::string &chname);
	void RmChannelInvite(std::string &chname);
};

#endif