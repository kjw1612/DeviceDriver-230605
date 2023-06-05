#pragma once
#include "FlashMemoryDevice.h"

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
    const int TOTAL_READ_RETRY_COUNT = 5;
    const int WRITE_INIT_STATE = 0xFF;
};