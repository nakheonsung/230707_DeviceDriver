#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:

    DeviceDriver(FlashMemoryDevice* hardware);
    bool ReadValidCheck(int nFirstRead, long address);
    int read(long address);
    bool IsWritable(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};
