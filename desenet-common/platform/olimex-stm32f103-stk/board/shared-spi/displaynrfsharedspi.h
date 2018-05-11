#ifndef DISPLAYNRFSHAREDSPI_H
#define DISPLAYNRFSHAREDSPI_H

#include "hal/spi.h"

/**
 * Shared part of the SPI used by the MonochromeDisplay and the
 * nRF chip.
 * The nRF chip has priority to use the SPI. Therefore, the
 * MonochomDisplay needs to reset the SPI to a state
 * that the nRF chip can use it directly.
 *
 * This class should not be accessed directly. Use the classes
 * NrfSpi and DisplaySpi to access this class.
 */
class DisplayNrfSharedSpi
{
	friend class NrfSpi;
	friend class DisplaySpi;

public:

	typedef Spi::tStatus tStatus;

	static DisplayNrfSharedSpi & instance();
	bool initialize();

protected:
	DisplayNrfSharedSpi();
	virtual ~DisplayNrfSharedSpi();

	DisplayNrfSharedSpi(const DisplayNrfSharedSpi &);															///< Forbids to copy an object.
	const DisplayNrfSharedSpi & operator =(const DisplayNrfSharedSpi & sspi) { (void)sspi; return sspi; }		///< Forbids to copy an application.


	inline Spi & spi() { return _SPI; }

	inline tStatus sendByte(unsigned char data) { return spi().sendByte(data); }

	void setSpiUsedByDisplay();
	void setSpiUsedByNrfTransceiver();

protected:
	bool _bInitialized;					///< Goes to true after calling the #initialize method.
	Spi & _SPI;							///< Reference to the real SPI (HAL interface)
};

#endif // DISPLAYNRFSHAREDSPI_H
