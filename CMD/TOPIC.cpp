#include "../INC/Server.hpp"

std::string Server::tTopic()
{
	std::time_t current = std::time(NULL);
	std::stringstream res;

	res << current;
	return res.str();
}

void Server::Topic(std::string &cmd, int &fd)
{
	std::vector<std::string> scmd = split_cmd(cmd);
	if (scmd.size() == 1)
		{senderror(403, "", fd, " :No such channel\r\n"); return;}
	std::string nmch = scmd[1].substr(1);
	if((scmd.size() == 2 && nmch == ":")|| !GetChannel(nmch))
	    {senderror(403, "#"+nmch, fd, " :No such channel\r\n"); return;}
	if (!(GetChannel(nmch)->get_client(fd)) && !(GetChannel(nmch)->get_admin(fd)))
	    {senderror(442, "#"+nmch, fd, " :You're not on that channel\r\n"); return;}
	if (scmd.size() == 2)
	{
		if (GetChannel(nmch)->GetTopicName() != "")
		{
			_sendResponse(": 332 " + GetClient(fd)->GetUserName() + " " + "#"+nmch + " :" + GetChannel(nmch)->GetTopicName() + "\r\n", fd);
			std::string rpl2 = ":localhost 333 " + GetClient(fd)->GetUserName() + " " + "#"+nmch + " " + GetClient(fd)->GetNickName() + " " + tTopic() + "\r\n";
			_sendResponse(rpl2, fd);
			return;
		}
		else
			_sendResponse(": 332 " + GetClient(fd)->GetUserName() + " " + "#"+nmch + " :" + GetChannel(nmch)->GetTopicName() + "\r\n", fd);return;
	}
	if (scmd.size() >= 3)
	{
		std::string restopic ;
		for (size_t i = 2; i < scmd.size(); i++)
			restopic += scmd[i] + " ";
		if (GetChannel(nmch)->Gettopic_restriction() && GetChannel(nmch)->get_client(fd))
			{senderror(442, nmch, fd, " :You're Not a channel operator\r\n");return;}
		else if (GetChannel(nmch)->Gettopic_restriction() && GetChannel(nmch)->get_admin(fd))
		{
			GetChannel(nmch)->SetTopicName(restopic);
			std::string rpl = ":" + GetClient(fd)->GetNickName() + "!" + GetClient(fd)->GetUserName() + "@localhost TOPIC #" + nmch + " :" + GetChannel(nmch)->GetTopicName() + "\r\n";

			GetChannel(nmch)->sendTo_all(rpl);
		}
		else
		{
			GetChannel(nmch)->SetTopicName(restopic);
			std::string rpl = ":" + GetClient(fd)->GetNickName() + "!" + GetClient(fd)->GetUserName() + "@localhost TOPIC #" + nmch + " :" + GetChannel(nmch)->GetTopicName() + "\r\n";
			GetChannel(nmch)->sendTo_all(rpl);
		}
	}
}