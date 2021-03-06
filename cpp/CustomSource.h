#ifndef SOURCESOCKET_IMPL_H
#define SOURCESOCKET_IMPL_H

#include "CustomSource_base.h"
#include "BoostServer.h"
#include "BoostClient.h"
#include "quickstats.h"
#include "vectorswap.h"

class CustomSource_i;

class CustomSource_i: public CustomSource_base {
ENABLE_LOGGING
public:
    CustomSource_i(const char *uuid, const char *label);
    ~CustomSource_i();
    int serviceFunction();

    void start() throw (CF::Resource::StartError, CORBA::SystemException);

private:
    template<typename T, typename U>
    void pushData(T* port, char* start, size_t numBytes, unsigned int numSwap) {
        if (port->state() != BULKIO::IDLE) {
            std::string name(port->getName());
            if (std::find(activePorts_.begin(), activePorts_.end(), name)
                    != activePorts_.end())
                activePorts_.push_back(name);
            assert(numBytes % sizeof(U) == 0);
            std::string streamID(theSri.streamID._ptr);
            if (numSwap == 1)
                numSwap = sizeof(U);
            if (numSwap > 1) {
                std::vector<U> output(numBytes / sizeof(U));
                if (numSwap != sizeof(U)) {
                    LOG_WARN(CustomSource_i,
                            "Data size " << sizeof(U) << " is not equal to byte swap size " << numSwap << ".");
                }
                vectorSwap(start, output, numSwap);
                tstamp_ = bulkio::time::utils::now();
                port->pushPacket(output, tstamp_, false, streamID);
            } else {
                U* out = reinterpret_cast<U*>(&start[0]);
                tstamp_ = bulkio::time::utils::now();
                port->pushPacket(out, numBytes/sizeof(U), tstamp_, false, streamID);
            }
        }
    }

    // Property Change Listener Callbacks
    void byte_swapChanged(const unsigned short *oldValue,
            const unsigned short *newValue);
    void connection_typeChanged(const std::string *oldValue,
            const std::string *newValue);
    void ip_addressChanged(const std::string *oldValue,
            const std::string *newValue);
    void max_bytesChanged(const CORBA::ULong *oldValue,
            const CORBA::ULong *newValue);
    void min_bytesChanged(const CORBA::ULong *oldValue,
            const CORBA::ULong *newValue);
    void portChanged(const unsigned short *oldValue,
            const unsigned short *newValue);
    void sriChanged(const sri_struct *oldValue, const sri_struct *newValue);
    void internal_buf_szChanged(const CORBA::ULong *oldValue,
            const CORBA::ULong *newValue);
    void socket_settingsChanged(const socket_settings_struct *oldValue,
            const socket_settings_struct *newValue);

    void updateXferLen();
    void updateSocket(bool starting=false);

    BULKIO::StreamSRI theSri;
    Server* server_;
    Client* client_;
    QuickStats stats_;
    std::vector<char> data_;
    size_t data_length_;
    size_t data_capacity_;
    boost::recursive_mutex socketLock_;
    boost::recursive_mutex xferLock_;
    BULKIO::PrecisionUTCTime tstamp_;
    size_t multSize_;
    std::vector<std::string> activePorts_;
    bool sendNewSri;
};

/*std::string hexStr(char* data, size_t len, size_t group=0){
    std::stringstream ss;
    ss << std::hex;
    for(size_t i=0;i<len;++i){
        if(i%40==0){
            ss << "\n";
        } else {
            ss << " ";
        }
        if(group>0 && i%group==0){
            ss << " 0x";
        }
        ss << std::setw(2) << std::setfill('0') << (int)data[i];
    }
    return ss.str();
}*/

#endif
