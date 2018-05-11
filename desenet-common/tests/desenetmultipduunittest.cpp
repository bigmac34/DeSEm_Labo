#include "desenetmultipduunittest.h"


void DesenetMultiPduUnitTest::setLength(desenet::MultiPdu & multiPdu, std::size_t length)
{
	multiPdu.setLength(length);
}

void DesenetMultiPduUnitTest::setePduCount(desenet::MultiPdu & multiPdu, uint8_t count)
{
	multiPdu.setePduCount(count);
}

void DesenetMultiPduUnitTest::setFrameData(desenet::MultiPdu & multiPdu, uint8_t * data, std::size_t dataLength)
{
	memcpy(multiPdu.buffer() + Frame::HEADER_SIZE, data, dataLength);
}
