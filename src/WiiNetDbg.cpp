#include "WiiNetDbg.h"


// constructeur :
WiiNetDbg::WiiNetDbg(std::string remip)
{
    s32 ret;
    // local ip configuration
    char localip[16] = {0};
    char gateway[16] = {0};
    char netmask[16] = {0};
    // local ip interface init
	ret = if_config ( localip, netmask, gateway, 1 /*TRUE*/, 20);

    if (ret>=0)
    {
        // UDP socket creation
        sockDbg = net_socket (PF_INET, SOCK_DGRAM, IPPROTO_IP);

        if (sockDbg == INVALID_SOCKET)
        {
            errorNumber = -2;
        }
        else
        {
            // UDP socket configuration
            memset (&clientDbg, 0, sizeof (clientDbg));

            clientDbg.sin_family = PF_INET;
            clientDbg.sin_port = htons (5555);
            clientDbg.sin_addr.s_addr = inet_addr(remip.c_str());
            clientDbg.sin_len = 8; // without this set to 8? it wont work (returns -22 on send)

            std::string initMessage = "Remote Debugger Initialised from ";
            initMessage = initMessage + localip + " to " + remip;
            RPrint(initMessage);
        }
    }

    else
        // local ip not initilazed, is wifi/bba
        errorNumber = -1;
}

// send an UDP packet over network to remote ip address
void WiiNetDbg::RPrint(std::string message)
{
    int n;
    int len = message.length();
    char * buf = new char[len];
    sprintf(buf,message.c_str());
    n = net_sendto(sockDbg,buf,len,0,(struct sockaddr*)&clientDbg,clientDbg.sin_len);
    if (n<0)
    {
        errorNumber = -3;
    }
    delete [] buf;
}

// returns errorNumber
int WiiNetDbg::getLastErrorNumber()
{
    return errorNumber;
}

WiiNetDbg::~WiiNetDbg()
{
    net_close(sockDbg);
}
