//*******************************************************************
// LPC17xx
//*******************************************************************
#include "lib.h"
#include "Hardware/Common/Font/Font_8x12.h"

//-------------------------------------------------------------------
cSystem sys;

cHwPinConfig::MAP cHwPinConfig::table[] = 
{
  // SPI
  SCK1_P0_7,
  MISO1_P0_8,
  MOSI1_P0_9,

  // UART
  TXD1_P2_0,
  RXD1_P2_1,

  END_OF_TABLE
};

//- Display ---------------------------------------------------------
#if defined DISP_TERMINAL
  cHwUART_N            uart( cHwUART_N::UART_1, cHwUART_N::BR_38400, 10, 10 );
  cHwPort_Terminal     portTerm( uart, 0 );
  cHwDisp_Terminal     dispHw  ( uart   ); 
  cDevDisplayChar      disp    ( dispHw );
#else 
  cHwPort_N              port0( cHwPort_N::P0 );
  cHwPort_N              port4( cHwPort_N::P4 );
  cHwSPImaster_1         spi( cHwSPImaster::CR_8000kHz, cHwSPImaster::CPOL_H_CPHA_H );
  cHwSPImaster::Device   spiLCD( spi, port0, 6);
  cHwPort::Pin           pinBL ( port4, 28 );
  cHwDisp_SPFD5408Bspi   dispHw( spiLCD, pinBL, fontFont_8x12, 2 );
  
  #if defined DISP_CHAR
    cDevDisplayChar      disp( dispHw );
  #elif defined DISP_GRAPHIC
    cDevDisplayGraphic   disp( dispHw );
  #else
    #error "config.h: Display type not defined"
  #endif
#endif

//*******************************************************************
