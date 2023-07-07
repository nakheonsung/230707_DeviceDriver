#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../230707_DeviceDriver/DeviceDriver.cpp"

using namespace std;
using namespace testing;

class HardwareMock : public FlashMemoryDevice
{
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestCaseName, HardwareMockTestRead) {
	HardwareMock HWMock;
	EXPECT_CALL(HWMock, read(0x1))
		.Times(5);

	DeviceDriver DD(&HWMock);
	DD.read(0x1);
}

TEST(TestCaseName, ReadSame5Times) {
	HardwareMock HWMock;
	EXPECT_CALL(HWMock, read(0x1))
		.Times(5)
		.WillRepeatedly(Return(0xFF));

	int expect = (int)(0xFF);
	DeviceDriver DD(&HWMock);
	EXPECT_THAT(expect, Eq(DD.read(0x1)));
}

TEST(TestCaseName, ReadNotSame5Times) {
	HardwareMock HWMock;
	EXPECT_CALL(HWMock, read(0x1))
		.Times(5)
		.WillOnce(Return(0x1))
		.WillRepeatedly(Return(0xFF));

	DeviceDriver DD(&HWMock);
	EXPECT_THROW(DD.read(0x1), exception);
}

TEST(TestCaseName, HardwareMockTestWrite) {
	HardwareMock HWMock;
	EXPECT_CALL(HWMock, read(0x1))
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	DeviceDriver DD(&HWMock);
	DD.write(0x1, 0xA);
}

TEST(TestCaseName, WriteNotClean) {
	HardwareMock HWMock;
	EXPECT_CALL(HWMock, read(0x1))
		.Times(1)
		.WillRepeatedly(Return(0xA));

	DeviceDriver DD(&HWMock);
	EXPECT_THROW(DD.write(0x1, 0xA), exception);
}