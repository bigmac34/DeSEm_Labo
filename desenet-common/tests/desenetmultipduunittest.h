#ifndef COMMON_TESTS_DESENET_MULTIPDU_UNITTEST_H
#define COMMON_TESTS_DESENET_MULTIPDU_UNITTEST_H

#include "unittest.h"
#include "desenet/multipdu.h"

/*
 * @brief Unit test class to access all methods and attributes of the desenet::MultiPdu class.
 *
 * Must only be used for test purpose.
 *
 */
class DesenetMultiPduUnitTest : public UnitTest
{
public:
	DesenetMultiPduUnitTest() {}
	virtual ~DesenetMultiPduUnitTest() {}

	void setLength(desenet::MultiPdu & multiPdu, std::size_t length);
	void setePduCount(desenet::MultiPdu & multiPdu, uint8_t count);
	void setFrameData(desenet::MultiPdu & multiPdu, uint8_t * data, std::size_t dataLength);
};

#endif // COMMON_TESTS_DESENET_MULTIPDU_UNITTEST_H
