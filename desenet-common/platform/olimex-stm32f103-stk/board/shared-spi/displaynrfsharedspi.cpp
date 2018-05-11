#include "stm32f10x_spi.h"
#include "hal/spi.h"
#include "displaynrfsharedspi.h"


DisplayNrfSharedSpi::DisplayNrfSharedSpi()
 : _bInitialized(false),
   _SPI(Spi::instance(0))
{

}

DisplayNrfSharedSpi::~DisplayNrfSharedSpi()
{

}

DisplayNrfSharedSpi::DisplayNrfSharedSpi(const DisplayNrfSharedSpi &)
 : _bInitialized(false),
   _SPI(Spi::instance(0))
{
}

// static
DisplayNrfSharedSpi & DisplayNrfSharedSpi::instance()
{
	static DisplayNrfSharedSpi sharedSpi;	// The only instance

	return sharedSpi;
}

bool DisplayNrfSharedSpi::initialize()
{
	if (!_bInitialized)
	{
		_bInitialized = true;

		spi().initialize();

		// Setup SPI to be used with the nRF chip
		setSpiUsedByNrfTransceiver();

		return true;
	}
	return false;
}

void DisplayNrfSharedSpi::setSpiUsedByDisplay()
{
	SPI_InitTypeDef  spiInitStructure;

	// Reset state machine of the SPI
	spi().resetStateMachine();

	// SPI1 configuration
	spiInitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spiInitStructure.SPI_Mode = SPI_Mode_Master;
	spiInitStructure.SPI_DataSize = SPI_DataSize_8b;
	spiInitStructure.SPI_CPOL = SPI_CPOL_High;
	spiInitStructure.SPI_CPHA = SPI_CPHA_2Edge;
	spiInitStructure.SPI_NSS = SPI_NSS_Soft;
	spiInitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	spiInitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	spiInitStructure.SPI_CRCPolynomial = 7;

	// Initialize SPI
	SPI_Init(SPI1, &spiInitStructure);

	// Enable SPI
	spi().enable();
}

void DisplayNrfSharedSpi::setSpiUsedByNrfTransceiver()
{
	SPI_InitTypeDef  spiInitStructure;

	// Reset state machine of the SPI
	spi().resetStateMachine();

	// SPI1 configuration
	spiInitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	spiInitStructure.SPI_Mode = SPI_Mode_Master;
	spiInitStructure.SPI_DataSize = SPI_DataSize_8b;
	spiInitStructure.SPI_CPOL = SPI_CPOL_Low;
	spiInitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	spiInitStructure.SPI_NSS = SPI_NSS_Soft;
	spiInitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_32;
	spiInitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	spiInitStructure.SPI_CRCPolynomial = 7;

	// Initialize SPI
	SPI_Init(SPI1, &spiInitStructure);

	// Enable SPI
	spi().enable();
}
