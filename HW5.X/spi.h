#ifndef SPI__H__
#define SPI__H__

void initSPI();
unsigned char spi_io(unsigned char o);
unsigned short generate(unsigned short v, int a_or_b);

#endif // SPI__H__