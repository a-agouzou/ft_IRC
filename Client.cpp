/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afatir <afatir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:28:06 by afatir            #+#    #+#             */
/*   Updated: 2024/01/22 21:35:43 by afatir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"

Client::Client(){}
Client::Client(std::string nickname, std::string username, int fd) : nickname(nickname), username(username), fd(fd){}
Client::~Client(){}
Client::Client(Client const &src){*this = src;}
Client &Client::operator=(Client const &src){
	if (this != &src){
		this->nickname = src.nickname;
		this->username = src.username;
		this->fd = src.fd;
	}
	return *this;
}

std::string Client::GetNickName(){return this->nickname;}
std::string Client::GetUserName(){return this->username;}
int Client::GetFd(){return this->fd;}