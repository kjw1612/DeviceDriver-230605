#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"../Project10/DeviceDriver.cpp"

using namespace std;
using namespace testing;

class MockDriver : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(Mission1, ReadFiveTest) {
	MockDriver mock_device;

	EXPECT_CALL(mock_device, read).Times(5);

	DeviceDriver driver(&mock_device);
	driver.read(0xA);
}

TEST(Mission1, ReadException) {
	MockDriver mock_device;

	EXPECT_CALL(mock_device, read(0x2))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x7))
		.WillOnce(Return(0x3));

	DeviceDriver driver(&mock_device);

	EXPECT_THROW(driver.read(0x2), std::exception);
}