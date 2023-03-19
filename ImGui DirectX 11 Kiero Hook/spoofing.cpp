#include "spoofing.h"

namespace acut
{
    static std::string ToLower(std::string str)
    {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        return str;
    }

    static std::vector<std::string> SplitStringWithDelimiter(std::string text, std::string delimiter)
    {
        std::vector<std::string> vStringParts;

        size_t iStart, iEnd = 0;

        while ((iStart = text.find_first_not_of(delimiter, iEnd)) != std::string::npos)
        {
            iEnd = text.find(delimiter, iStart);
            vStringParts.push_back(text.substr(iStart, iEnd - iStart));
        }

        return vStringParts;
    }
}

namespace spoofing
{
    void spoof_info_response(Msg_InfoResponse* response)
    {
        response->natType = 1;

        for (int i = 0; i < 2; i++)
        {
            if (spoof_netadr)
            {
                response->lobby[i].serializedAdr = { 0 };
                response->lobby[i].isValid = { 0 };
                response->lobby[i].secId = { 0 };
                response->lobby[i].secKey = { 0 };
                response->lobby[i].hostXuid = { 0 };

                /*
                std::string IpOverride(spoofing);

                std::vector<std::string> IpOverride = acut::SplitStringWithDelimiter(IpOverride, ".");
                LPBYTE IPAddress = (LPBYTE)FindDmaAddy(dwXnAddr, std::vector<std::uintptr_t>({ 0xE0, 0x90, 0x38, 0x58, 0x14 }));

                IPAddress[0] = (BYTE)strtol(IpOverride[0].c_str(), NULL, 10);
                IPAddress[1] = (BYTE)strtol(IpOverride[1].c_str(), NULL, 10);
                IPAddress[2] = (BYTE)strtol(IpOverride[2].c_str(), NULL, 10);
                IPAddress[3] = (BYTE)strtol(IpOverride[3].c_str(), NULL, 10);
                */
            }
        }
    }
}
