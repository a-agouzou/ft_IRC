/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khbouych <khbouych@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:19:08 by afatir            #+#    #+#             */
/*   Updated: 2024/01/31 14:35:24 by khbouych         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"

Channel::Channel(){
	this->invit_only = 0;
	this->topic = 0;
	this->key = 0;
	this->limit = 0;
	this->topic_name = "";
	this->name = "";
}
Channel::~Channel(){}
Channel::Channel(Channel const &src){
	*this = src;
}
Channel &Channel::operator=(Channel const &src){
	if (this != &src){
		this->name = src.name;
		this->clients = src.clients;
		this->admins = src.admins;
		this->invit_only = src.invit_only;
		this->topic = src.topic;
		this->key = src.key;
		this->limit = src.limit;
		this->topic_name = src.topic_name;
		this->password = src.password;
	}
	return *this;
}
//###########################################################
void Channel::SetInvitOnly(int invit_only){this->invit_only = invit_only;}
void Channel::SetTopic(int topic){this->topic = topic;}
void Channel::SetKey(int key){this->key = key;}
void Channel::SetLimit(int limit){this->limit = limit;}
void Channel::SetTopicName(std::string topic_name){this->topic_name = topic_name;}
void Channel::SetPassword(std::string password){this->password = password;}
void Channel::SetName(std::string name){this->name = name;}
//###########################################################
int Channel::GetInvitOnly(){return this->invit_only;}
int Channel::GetTopic(){return this->topic;}
int Channel::GetKey(){return this->key;}
int Channel::GetLimit(){return this->limit;}
std::string Channel::GetTopicName(){return this->topic_name;}
std::string Channel::GetPassword(){return this->password;}
std::string Channel::GetName(){return this->name;}
std::string Channel::clientChannel_list()
{
	std::string list;
	for(size_t i = 0; i < admins.size(); i++)
	{
		list += "@" + admins[i].GetNickName();
		if((i + 1) < admins.size())
			list += " ";
	}
	if(clients.size())
		list += " ";
	for(size_t i = 0; i < clients.size(); i++)
	{
		list += clients[i].GetNickName();
		if((i + 1) < clients.size())
			list += " ";
	}
	return list;
}
//###########################################################
void Channel::add_client(Client newClient){clients.push_back(newClient);}
void Channel::add_admin(Client newClient){admins.push_back(newClient);}
Client *Channel::get_client(int fd){
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it){
		if (it->GetFd() == fd)
			return &(*it);
	}
	return NULL;
}
Client *Channel::get_admin(int fd){
	for (std::vector<Client>::iterator it = admins.begin(); it != admins.end(); ++it){
		if (it->GetFd() == fd)
			return &(*it);
	}
	return NULL;
}
void Channel::remove_client(int fd){
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it){
		if (it->GetFd() == fd)
			{clients.erase(it); break;}
	}
}
void Channel::remove_admin(int fd){
	for (std::vector<Client>::iterator it = admins.begin(); it != admins.end(); ++it){
		if (it->GetFd() == fd)
			{admins.erase(it); break;}
	}
}
int Channel::GetClientsNumber(){return this->clients.size() + this->admins.size();}
Client* Channel::GetClientInChannel(std::string name){
	for (std::vector<Client>::iterator it = clients.begin(); it != clients.end(); ++it){
		if (it->GetNickName() == name)
			return &(*it);
	}
	for (std::vector<Client>::iterator it = admins.begin(); it != admins.end(); ++it){
		if (it->GetNickName() == name)
			return &(*it);
	}
	return NULL;
}

// abdellah
void Channel::sendTo_all(std::string &rpl1, std::string &rpl2 , std::string &rpl3)
{
	std::string cli_list = this->clientChannel_list();
	for(size_t i = 0; i < admins.size(); i++)
	{
			send(admins[i].GetFd(), rpl1.c_str(), rpl1.size(),0);
			send(admins[i].GetFd(), rpl2.c_str(), rpl2.size(),0);
			send(admins[i].GetFd(), rpl3.c_str(), rpl3.size(),0);
	}
	for(size_t i = 0; i < clients.size(); i++)
	{
			send(clients[i].GetFd(), rpl1.c_str(), rpl1.size(),0);
			send(clients[i].GetFd(), rpl2.c_str(), rpl2.size(),0);
			send(clients[i].GetFd(), rpl3.c_str(), rpl3.size(),0);
	}
}
void Channel::sendTo_all(std::string &rpl1)
{
	// std::string cli_list = this->clientChannel_list();
	for(size_t i = 0; i < admins.size(); i++)
	{
			std::cout << "     admins i: " << clients.size() << std::endl; 
			send(admins[i].GetFd(), rpl1.c_str(), rpl1.size(),0);
	}
	
	for(size_t i = 0; i < clients.size(); i++)
	{
			std::cout << "     cli i: " << clients.size() << std::endl; 
			send(clients[i].GetFd(), rpl1.c_str(), rpl1.size(),0);
	}
}
void Channel::sendTo_all(std::string &rpl1, int fd)
{
	// std::string cli_list = this->clientChannel_list();
	for(size_t i = 0; i < admins.size(); i++)
	{
		if(admins[i].GetFd() != fd)
			send(admins[i].GetFd(), rpl1.c_str(), rpl1.size(),0);
		std::cout << "     admins i: " << clients.size() << std::endl; 
	}
	
	for(size_t i = 0; i < clients.size(); i++)
	{
		std::cout << "     cli i: " << clients.size() << std::endl; 
		if(clients[i].GetFd() != fd)
			send(clients[i].GetFd(), rpl1.c_str(), rpl1.size(),0);
	}
}