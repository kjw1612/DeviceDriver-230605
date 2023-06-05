#include "DeviceDriver.h"

class Application
{
public:
	explicit Application(DeviceDriver* driver) : stDriver(driver){}

	void ReadAndPrint(int startAddress, int endAddress)
	{
		for(int i = startAddress; i <= endAddress; i++)
		{
			int ret = stDriver->read(i);
		}
	}

	void WriteAll(int value)
	{
		for(int i = 0; i <= 0x4; i++)
		{
			stDriver->write(i, value);
		}
	}

private:
	DeviceDriver* stDriver;
};