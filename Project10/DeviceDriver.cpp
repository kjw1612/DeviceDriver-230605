#include "DeviceDriver.h"
#include <Windows.h>
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

class ReadFailException : public std::exception{};
class WriteFailException : public std::exception {};

int DeviceDriver::read(long address)
{
    int firstReadTryValue = m_hardware->read(address);

    for (int readRetryCount = 1; readRetryCount < TOTAL_READ_RETRY_COUNT; readRetryCount++)
    {
        int nextReadTryValue = m_hardware->read(address);
        if (firstReadTryValue != nextReadTryValue)
        {
            throw std::exception("ReadFailException!!");
        }        
    }
    return firstReadTryValue;
}

void DeviceDriver::write(long address, int data)
{
    if(m_hardware->read(address) == 0xFF)
    {
        m_hardware->write(address, (unsigned char)data);
    }
    else
    {
        throw std::exception("WriteFailException!!");
    }
    
}