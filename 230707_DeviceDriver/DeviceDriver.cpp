#include "DeviceDriver.h"
#include <stdexcept>
using namespace std;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

bool DeviceDriver::ReadValidCheck(int nFirstRead, long address)
{
    bool bReturn = true;;
    static const int RETRY_READ = 4;
	for (int i=0; i< RETRY_READ; i++)
	{
		if (nFirstRead != (int)m_hardware->read(address))
		{
            bReturn = false;
		}
	}
    return bReturn;
}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int nRead = (int)m_hardware->read(address);
    if (!ReadValidCheck(nRead, address))
    {
        throw exception("ReadFailException, Must be same Number in 5 Times");
    }
    return nRead;
}

bool DeviceDriver::IsWritable(long address)
{
    static const int CLEAN_READ = 0xFF;
	if (CLEAN_READ != (int)m_hardware->read(address))
	{
		return false;
	}
    return true;
}

void DeviceDriver::write(long address, int data)
{
    if (IsWritable(address) == false)
    {
        throw exception("WriteFailException, Must be clean (0xFF)");
    }
    m_hardware->write(address, (unsigned char)data);
}
