#ifndef WIINETDBG_H
#define WIINETDBG_H

#include <string>
#include <string.h>

// include for wii network
#include <network.h>

class WiiNetDbg
{
    public:
        // constructor : remote ip address must be given
        WiiNetDbg(std::string remip);
        // send UDP message over network to remote ip address
        void RPrint(std::string message);
        // returns errorNumber
        int getLastErrorNumber();
        // destructor
        virtual ~WiiNetDbg();

    private:
        // last operation error number
        int errorNumber;
        // socket for the debugger
        s32 sockDbg;
        // socckaddr of the remote client
        struct sockaddr_in clientDbg;
};

#endif // WIINETDBG_H
