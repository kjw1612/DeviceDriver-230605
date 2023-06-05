#include<gtest/gtest.h>
#include<gmock/gmock.h>
#include"../Project10/DeviceDriver.cpp"
#include"../Project10/app.cpp"
#include<iostream>

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

TEST(Mission1, WriteTest) {
	MockDriver mock_device;
	DeviceDriver driver(&mock_device);

	EXPECT_CALL(mock_device, read(0x00)).WillOnce(Return(0xFF));
	driver.write(0x00, 0x1f);
}


TEST(Mission1, WriteExceptionTest) {
	MockDriver mock_device;
	DeviceDriver driver(&mock_device);

	EXPECT_CALL(mock_device, read(0x00)).WillOnce(Return(0x1F));

	EXPECT_THROW(driver.write(0x00, 0x1f), std::exception);
}

TEST(Mission1, WhenWriteThenReadOneTime)
{
	MockDriver mock_device;
	DeviceDriver driver(&mock_device);

	EXPECT_CALL(mock_device, read(0x00))
		.Times(1)
		.WillOnce(Return(0xFF));

	driver.write(0x00, 0x1F);
}


TEST(Mission1, WhenWriteThen0xFE)
{
	MockDriver mock_device;
	DeviceDriver driver(&mock_device);

	EXPECT_CALL(mock_device, read(0x00))
		.WillOnce(Return(0xFE));

	EXPECT_THROW(driver.write(0x00, 0x1F), std::exception);
}

TEST(Mission1, Application_read) {
	MockDriver mock_device;
	EXPECT_CALL(mock_device, read(_))
		.Times(25);

	DeviceDriver driver(&mock_device);
	Application app(&driver);

	app.ReadAndPrint(0x00, 0x04);
}