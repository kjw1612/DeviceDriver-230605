#include "DeviceDriver.h"
#include <Windows.h>
#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    int firstReadTryValue = m_hardware->read(address);

    for (int i = 1;i < TotalReadTryCount; i++)
    {
        Sleep(200);
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
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}