#include <msp430.h>

#include "hal_spi.h"

void hal_SPI_Init(spi_settings_t* settings){
	// Disable
	hal_SPI_Disable(settings->channel);
	switch(settings->channel){
		case SPI_A0:
			// Setup MOSI, MISO
			P3SEL |= BIT3 + BIT4;
			// Setup SCLK
			P2SEL |= BIT7;
			// Use SMCLK
			UCA0CTL1 |= UCSSEL_2;
			// Configure settings
			UCA0CTL0 |= (settings->mode & BIT1) ? (UCCKPL) : 0;
			UCA0CTL0 |= (settings->mode & BIT0) ? 0: (UCCKPH);
			UCA0CTL0 |= (settings->hal_settings.msb_first) ? (UCMSB) : 0;
			UCA0CTL0 |= (settings->hal_settings.char7bit) ? (UC7BIT) : 0;
			// Configure bit rate
			UCA0BR0 = FCPU / settings->bit_rate;
			UCA0BR1 = FCPU / settings->bit_rate / 256;
			// Configure DMA
			if (settings->hal_settings.use_dma && settings->hal_settings.DMA_buffer) {
				// If channel 0 isn't enabled yet
				if (~(DMA0CTL & DMAEN)) {
					// Set channel zero to trigger on UCA0 receives something
					DMACTL0 |= DMA0TSEL_16;
					// Set the buffer size
					DMA0SZ = DMA_BUFFER_SIZE;//settings->hal_settings.dma_buf_size;
					// Repeated single transfer, increment the destination address, source byte to destination byte
					DMA0CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					// Enable DMA and interrupts
					DMA0CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA0SA, (unsigned long) &UCA0RXBUF);
					// Set the destination address
					__data20_write_long((unsigned long) &DMA0DA, (unsigned long) settings->hal_settings.DMA_buffer);

				}
				// Or channel 1
				else if(~(DMA1CTL & DMAEN)) {
					// Set channel one to trigger on UCA0 receives something
					DMACTL0 |= DMA1TSEL_16;
					// Set the buffer size
					DMA1SZ = DMA_BUFFER_SIZE;//settings->hal_settings.dma_buf_size;
					// Repeated single transfer, increment the destination address, source byte to destination byte
					DMA1CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					// Enable DMA and interrupts
					DMA1CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA1SA, (unsigned long) &UCA0RXBUF);
					// Set the destination address
					__data20_write_long((unsigned long) &DMA1DA, (unsigned long) settings->hal_settings.DMA_buffer);

				}
				// Or channel 2
				else if(~(DMA2CTL & DMAEN)) {
					// Set channel two to trigger on UCA0 receives something
					DMACTL1 |= DMA2TSEL_16;
					// Set the source address
					__data20_write_long((unsigned long) &DMA2SA, (unsigned long) &UCA0RXBUF);
					// Set the destination address
					__data20_write_long((unsigned long) &DMA2DA, (unsigned long) settings->hal_settings.DMA_buffer);
					// Set the buffer size
					DMA2SZ = DMA_BUFFER_SIZE;//settings->hal_settings.dma_buf_size;
					// Repeated single transfer, increment the destination address, source byte to destination byte
					DMA2CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					// Enable DMA and interrupts
					DMA2CTL |= DMAEN | DMAIE;
				}
				// Turn off DMA in spi settings, user can check if this has changed
				else {
					settings->hal_settings.use_dma = 0;
				}
			}
			break;
		case SPI_A1:
			// Setup MOSI, MISO
			P4SEL |= BIT5 + BIT4;
			// Setup SCLK
			P4SEL |= BIT0;
			// Use SMCLK
			UCA1CTL1 |= UCSSEL_2;
			// Configure settings
			UCA1CTL0 |= (settings->mode & BIT1) ? (UCCKPL) : 0;
			UCA1CTL0 |= (settings->mode & BIT0) ? 0: (UCCKPH);
			UCA1CTL0 |= (settings->hal_settings.msb_first) ? (UCMSB) : 0;
			UCA1CTL0 |= (settings->hal_settings.char7bit) ? (UC7BIT) : 0;
			// Configure bit rate
			UCA1BR0 = FCPU / settings->bit_rate;
			UCA1BR1 = FCPU / settings->bit_rate / 256;

			if (settings->hal_settings.use_dma && settings->hal_settings.DMA_buffer) {
				if (~(DMA0CTL & DMAEN)) {
					DMACTL0 |= DMA0TSEL_20;
					DMA0SZ = DMA_BUFFER_SIZE;
					DMA0CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA0CTL |= DMAEN | DMAIE;
					__data20_write_long((unsigned long) &DMA0SA, (unsigned long) &UCA1RXBUF);
					__data20_write_long((unsigned long) &DMA0DA, (unsigned long) settings->hal_settings.DMA_buffer);

				}
				else if(~(DMA1CTL & DMAEN)) {
					DMACTL0 |= DMA1TSEL_20;
					DMA1SZ = DMA_BUFFER_SIZE;
					DMA1CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA1CTL |= DMAEN | DMAIE;
					__data20_write_long((unsigned long) &DMA1SA, (unsigned long) &UCA1RXBUF);
					__data20_write_long((unsigned long) &DMA1DA, (unsigned long) settings->hal_settings.DMA_buffer);
				}
				else if(~(DMA2CTL & DMAEN)) {
					DMACTL1 |= DMA2TSEL_20;
					DMA2SZ = DMA_BUFFER_SIZE;
					DMA2CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA2CTL |= DMAEN | DMAIE;
					__data20_write_long((unsigned long) &DMA2SA, (unsigned long) &UCA1RXBUF);
					__data20_write_long((unsigned long) &DMA2DA, (unsigned long) settings->hal_settings.DMA_buffer);
				}
				else {
					settings->hal_settings.use_dma = 0;
				}
			}
			break;
		case SPI_B0:
			// Setup MOSI, MISO, SCLK
			P3SEL |= BIT0 + BIT1 + BIT2;
			// Use SMCLK
			UCB0CTL1 |= UCSSEL_2;
			// Configure settings
			UCB0CTL0 |= (settings->mode & BIT1) ? (UCCKPL) : 0;
			UCB0CTL0 |= (settings->mode & BIT0) ? 0: (UCCKPH);
			UCB0CTL0 |= (settings->hal_settings.msb_first) ? (UCMSB) : 0;
			UCB0CTL0 |= (settings->hal_settings.char7bit) ? (UC7BIT) : 0;
			UCB0CTL0 |= UCMST;
			// Configure bit rate
			UCB0BR0 = FCPU / settings->bit_rate;
			UCB0BR1 = FCPU / settings->bit_rate / 256;

			if (settings->hal_settings.use_dma && settings->hal_settings.DMA_buffer) {
				if (~(DMA0CTL & DMAEN)) {
					DMACTL0 |= DMA0TSEL_18;
					DMA0CTL &= ~DMAIFG;
					DMA0CTL = DMADT_4 + DMADSTINCR_3 + DMASBDB;
					DMA0CTL |= DMAEN + DMAIE;
					DMA0SZ = DMA_BUFFER_SIZE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA0SA, (unsigned long) &UCB0RXBUF);
					__data20_write_long((unsigned long) &DMA0DA, (unsigned long) settings->hal_settings.DMA_buffer);

				}
				else if(~(DMA1CTL & DMAEN)) {
					DMACTL0 |= DMA1TSEL_18;
					DMA1SZ = DMA_BUFFER_SIZE;
					DMA1CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA1CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA1SA, (unsigned long) &UCB0RXBUF);
					__data20_write_long((unsigned long) &DMA1DA, (unsigned long) settings->hal_settings.DMA_buffer);

				}
				else if(~(DMA2CTL & DMAEN)) {
					DMACTL1 |= DMA2TSEL_18;
					DMA2SZ = DMA_BUFFER_SIZE;
					DMA2CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA2CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA2SA, (unsigned long) &UCB0RXBUF);
					__data20_write_long((unsigned long) &DMA2DA, (unsigned long) settings->hal_settings.DMA_buffer);
				}
				else {
					settings->hal_settings.use_dma = 0;
				}
			}
			break;
		case SPI_B1:
			// Setup MOSI, MISO
			P4SEL |= BIT1 + BIT2;
			// Setup SCLK
			P4SEL |= BIT3;
			// Use SMCLK
			UCB1CTL1 |= UCSSEL_2;
			// Configure settings
			UCB1CTL0 |= (settings->mode & BIT1) ? (UCCKPL) : 0;
			UCB1CTL0 |= (settings->mode & BIT0) ? 0: (UCCKPH);
			UCB1CTL0 |= (settings->hal_settings.msb_first) ? (UCMSB) : 0;
			UCB1CTL0 |= (settings->hal_settings.char7bit) ? (UC7BIT) : 0;
			// Configure bit rate
			UCB1BR0 = FCPU / settings->bit_rate;
			UCB1BR1 = FCPU / settings->bit_rate / 256;

			if (settings->hal_settings.use_dma && settings->hal_settings.DMA_buffer) {
				if (~(DMA0CTL & DMAEN)) {
					DMACTL0 |= DMA0TSEL_22;
					DMA0SZ = DMA_BUFFER_SIZE;
					DMA0CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA0CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA0SA, (unsigned long) &UCB1RXBUF);
					__data20_write_long((unsigned long) &DMA0DA, (unsigned long) settings->hal_settings.DMA_buffer);

				}
				else if(~(DMA1CTL & DMAEN)) {
					DMACTL0 |= DMA1TSEL_22;
					DMA1SZ = DMA_BUFFER_SIZE;
					DMA1CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA1CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA1SA, (unsigned long) &UCB1RXBUF);
					__data20_write_long((unsigned long) &DMA1DA, (unsigned long) settings->hal_settings.DMA_buffer);


				}
				else if(~(DMA2CTL & DMAEN)) {
					DMACTL1 |= DMA2TSEL_22;
					DMA2SZ = DMA_BUFFER_SIZE;
					DMA2CTL = DMADT_4 | DMADSTINCR_3 | DMASBDB;
					DMA2CTL |= DMAEN | DMAIE;
					// Set the source address
					__data20_write_long((unsigned long) &DMA2SA, (unsigned long) &UCB1RXBUF);
					__data20_write_long((unsigned long) &DMA2DA, (unsigned long) settings->hal_settings.DMA_buffer);
				}
				else {
					settings->hal_settings.use_dma = 0;
				}
			}
			break;
	}
	hal_SPI_Enable(settings->channel);
	hal_SPI_ClearRxIF(settings->channel);

	if(settings->hal_settings.use_dma == 0) {
		hal_SPI_EnableRxInterrupt(settings->channel);
	} else {
		hal_SPI_DisableRxInterrupt(settings->channel);
	}
}

void hal_SPI_Enable(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0CTL1 &= ~(UCSWRST);
			break;
		case SPI_A1:
			UCA1CTL1 &= ~(UCSWRST);
			break;
		case SPI_B0:
			UCB0CTL1 &= ~(UCSWRST);
			break;
		case SPI_B1:
			UCB1CTL1 &= ~(UCSWRST);
			break;
		default:
			return;
	}
}

void hal_SPI_Disable(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0CTL1 |= UCSWRST;
			break;
		case SPI_A1:
			UCA1CTL1 |= UCSWRST;
			break;
		case SPI_B0:
			UCB0CTL1 |= UCSWRST;
			break;
		case SPI_B1:
			UCB1CTL1 |= UCSWRST;
			break;
		default:
			return;
	}
}

void hal_SPI_EnableRxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0IE |= UCRXIE;
			break;
		case SPI_A1:
			UCA1IE |= UCRXIE;
			break;
		case SPI_B0:
			UCB0IE |= UCRXIE;
			break;
		case SPI_B1:
			UCB1IE |= UCRXIE;
			break;
		default:
			return;
	}
}

void hal_SPI_EnableTxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0IE |= UCTXIE;
			break;
		case SPI_A1:
			UCA1IE |= UCTXIE;
			break;
		case SPI_B0:
			UCB0IE |= UCTXIE;
			break;
		case SPI_B1:
			UCB1IE |= UCTXIE;
			break;
		default:
			return;
	}
}

void hal_SPI_DisableRxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0IE &= ~UCRXIE;
			break;
		case SPI_A1:
			UCA1IE &= ~UCRXIE;
			break;
		case SPI_B0:
			UCB0IE &= ~UCRXIE;
			break;
		case SPI_B1:
			UCB1IE &= ~UCRXIE;
			break;
		default:
			return;
	}
}

void hal_SPI_DisableTxInterrupt(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0IE &= ~UCTXIE;
			break;
		case SPI_A1:
			UCA1IE &= ~UCTXIE;
			break;
		case SPI_B0:
			UCB0IE &= ~UCTXIE;
			break;
		case SPI_B1:
			UCB1IE &= ~UCTXIE;
			break;
		default:
			return;
	}
}

uint8_t hal_SPI_TxIntStatus(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return (UCA0IFG & UCTXIFG) >> 1;
		case SPI_A1:
			return (UCA1IFG & UCTXIFG) >> 1;
		case SPI_B0:
			return (UCB0IFG & UCTXIFG) >> 1;
		case SPI_B1:
			return (UCB1IFG & UCTXIFG) >> 1;
		default:
			return 0;
	}
}

uint8_t hal_SPI_IsTxIntEnabled(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return (UCA0IE & UCTXIE) >> 1;
		case SPI_A1:
			return (UCA1IE & UCTXIE) >> 1;
		case SPI_B0:
			return (UCB0IE & UCTXIE) >> 1;
		case SPI_B1:
			return (UCB1IE & UCTXIE) >> 1;
		default:
			return 0;
	}
}

uint8_t hal_SPI_RxIntStatus(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return (UCA0IFG & UCRXIFG);
		case SPI_A1:
			return (UCA1IFG & UCRXIFG);
		case SPI_B0:
			return (UCB0IFG & UCRXIFG);
		case SPI_B1:
			return (UCB1IFG & UCRXIFG);
		default:
			return 0;
	}
}

void hal_SPI_TxByte(uint8_t channel, uint8_t b){
	switch(channel){
		case SPI_A0:
			UCA0TXBUF = b;
			break;
		case SPI_A1:
			UCA1TXBUF = b;
			break;
		case SPI_B0:
			UCB0TXBUF = b;
			break;
		case SPI_B1:
			UCB1TXBUF = b;
			break;
		default:
			return;
	}
}

uint8_t hal_SPI_RxByte(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return UCA0RXBUF;
		case SPI_A1:
			return UCA1RXBUF;
		case SPI_B0:
			return UCB0RXBUF;
		case SPI_B1:
			return UCB1RXBUF;
		default:
			return 0;
	}
}

void hal_SPI_ClearRxIF(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0IFG &= ~UCRXIFG;
			break;
		case SPI_A1:
			UCA1IFG &= ~UCRXIFG;
			break;
		case SPI_B0:
			UCB0IFG &= ~UCRXIFG;
			break;
		case SPI_B1:
			UCB1IFG &= ~UCRXIFG;
			break;
		default:
			return;
	}
}

void hal_SPI_ClearTxIF(uint8_t channel){
	switch(channel){
		case SPI_A0:
			UCA0IFG &= ~UCTXIFG;
			break;
		case SPI_A1:
			UCA1IFG &= ~UCTXIFG;
			break;
		case SPI_B0:
			UCB0IFG &= ~UCTXIFG;
			break;
		case SPI_B1:
			UCB1IFG &= ~UCTXIFG;
			break;
		default:
			return;
	}
}

uint8_t hal_SPI_SpaceAvailable(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return (UCA0IFG & UCTXIFG);
		case SPI_A1:
			return (UCA1IFG & UCTXIFG);
		case SPI_B0:
			return (UCB0IFG & UCTXIFG);
		case SPI_B1:
			return (UCB1IFG & UCTXIFG);
		default:
			return 0;
	}
}

uint8_t hal_SPI_DataAvailable(uint8_t channel){
	switch(channel){
		case SPI_A0:
			return (UCA0IFG & UCRXIFG);
		case SPI_A1:
			return (UCA1IFG & UCRXIFG);
		case SPI_B0:
			return (UCB0IFG & UCRXIFG);
		case SPI_B1:
			return (UCB1IFG & UCRXIFG);
		default:
			return 0;
	}
}

uint8_t hal_SPI_OverrunError(uint8_t channel) {
	switch(channel){
		case SPI_A0:
			return (UCA0STAT & UCOE);
		case SPI_A1:
			return (UCA1STAT & UCOE);
		case SPI_B0:
			return (UCB0STAT & UCOE);
		case SPI_B1:
			return (UCB1STAT & UCOE);
		default:
			return 0;
	}
}

uint8_t hal_SPI_UsingDMA(uint8_t channel) {
	switch(channel){
	case SPI_A0:
		return ((DMACTL0 & DMA0TSEL_16) | (DMACTL0 & DMA1TSEL_16) | (DMACTL0 & DMA2TSEL_16));
	case SPI_A1:
		return ((DMACTL0 & DMA0TSEL_20) | (DMACTL0 & DMA1TSEL_20) | (DMACTL0 & DMA2TSEL_20));
	case SPI_B0:
		return ((DMACTL0 & DMA0TSEL_18) | (DMACTL0 & DMA1TSEL_18) | (DMACTL0 & DMA2TSEL_18));
	case SPI_B1:
		return ((DMACTL0 & DMA0TSEL_22) | (DMACTL0 & DMA1TSEL_22) | (DMACTL0 & DMA2TSEL_22));
	default:
		return 0;
	}
}

void hal_SPI_ClearDMABuffer(uint8_t channel) {
	switch(channel){
	case SPI_A0:
		if (DMACTL0 & DMA0TSEL_16) {
			DMA0DA -= (DMA_BUFFER_SIZE - DMA0SZ);
			DMA0SZ += (DMA_BUFFER_SIZE - DMA0SZ);
			return;
		}
		else if (DMACTL0 & DMA1TSEL_16) {
			DMA1DA -= (DMA_BUFFER_SIZE - DMA1SZ);
			DMA1SZ += (DMA_BUFFER_SIZE - DMA1SZ);
			return;
		}
		else if (DMACTL0 & DMA2TSEL_16) {
			DMA2DA -= (DMA_BUFFER_SIZE - DMA2SZ);
			DMA2SZ += (DMA_BUFFER_SIZE - DMA2SZ);
			return;
		}
		else {
			return;
		}
		break;
	case SPI_A1:
		if (DMACTL0 & DMA0TSEL_20) {
			DMA0DA -= (DMA_BUFFER_SIZE - DMA0SZ);
			DMA0SZ += (DMA_BUFFER_SIZE - DMA0SZ);
			return;
		}
		else if (DMACTL0 & DMA1TSEL_20) {
			DMA1DA -= (DMA_BUFFER_SIZE - DMA1SZ);
			DMA1SZ += (DMA_BUFFER_SIZE - DMA1SZ);
			return;
		}
		else if (DMACTL0 & DMA2TSEL_20) {
			DMA2DA -= (DMA_BUFFER_SIZE - DMA2SZ);
			DMA2SZ += (DMA_BUFFER_SIZE - DMA2SZ);
			return;
		}
		else {
			return;
		}
		break;
	case SPI_B0:
		if (DMACTL0 & DMA0TSEL_18) {
			DMA0DA -= (DMA_BUFFER_SIZE - DMA0SZ);
			DMA0SZ += (DMA_BUFFER_SIZE - DMA0SZ);
			return;
		}
		else if (DMACTL0 & DMA1TSEL_18) {
			DMA1DA -= (DMA_BUFFER_SIZE - DMA1SZ);
			DMA1SZ += (DMA_BUFFER_SIZE - DMA1SZ);
			return;
		}
		else if (DMACTL0 & DMA2TSEL_18) {
			DMA2DA -= (DMA_BUFFER_SIZE - DMA2SZ);
			DMA2SZ += (DMA_BUFFER_SIZE - DMA2SZ);
			return;
		}
		else {
			return;
		}
		break;
	case SPI_B1:
		if (DMACTL0 & DMA0TSEL_22) {
			DMA0DA -= (DMA_BUFFER_SIZE - DMA0SZ);
			DMA0SZ += (DMA_BUFFER_SIZE - DMA0SZ);
			return;
		}
		else if (DMACTL0 & DMA1TSEL_22) {
			DMA1DA -= (DMA_BUFFER_SIZE - DMA1SZ);
			DMA1SZ += (DMA_BUFFER_SIZE - DMA1SZ);
			return;
		}
		else if (DMACTL0 & DMA2TSEL_22) {
			DMA2DA -= (DMA_BUFFER_SIZE - DMA2SZ);
			DMA2SZ += (DMA_BUFFER_SIZE - DMA2SZ);
			return;
		}
		else {
			return;
		}
		break;
	default:
		return;
	}
}

void hal_SPI_SetDMABuffer(uint8_t channel, uint8_t* buffer) {
	switch(channel){
	case SPI_A0:
		if (DMACTL0 & DMA0TSEL_16) {
			__data16_write_addr((unsigned short) &DMA0DA, (unsigned long) buffer);
			DMA0SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA1TSEL_16) {
			__data16_write_addr((unsigned short) &DMA1DA, (unsigned long) buffer);
			DMA1SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA2TSEL_16) {
			__data16_write_addr((unsigned short) &DMA2DA, (unsigned long) buffer);
			DMA2SZ = DMA_BUFFER_SIZE;
			return;
		}
		else {
			return;
		}
		break;
	case SPI_A1:
		if (DMACTL0 & DMA0TSEL_20) {
			__data16_write_addr((unsigned short) &DMA0DA, (unsigned long) buffer);
			DMA0SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA1TSEL_20) {
			__data16_write_addr((unsigned short) &DMA1DA, (unsigned long) buffer);
			DMA1SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA2TSEL_20) {
			__data16_write_addr((unsigned short) &DMA2DA, (unsigned long) buffer);
			DMA2SZ = DMA_BUFFER_SIZE;
			return;
		}
		else {
			return;
		}
		break;
	case SPI_B0:
		if (DMACTL0 & DMA0TSEL_18) {
			__data16_write_addr((unsigned short) &DMA0DA, (unsigned long) buffer);
			DMA0SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA1TSEL_18) {
			__data16_write_addr((unsigned short) &DMA1DA, (unsigned long) buffer);
			DMA1SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA2TSEL_18) {
			__data16_write_addr((unsigned short) &DMA2DA, (unsigned long) buffer);
			DMASZ = DMA_BUFFER_SIZE;
			return;
		}
		else {
			return;
		}
		break;
	case SPI_B1:
		if (DMACTL0 & DMA0TSEL_22) {
			__data16_write_addr((unsigned short) &DMA0DA, (unsigned long) buffer);
			DMA0SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA1TSEL_22) {
			__data16_write_addr((unsigned short) &DMA1DA, (unsigned long) buffer);
			DMA1SZ = DMA_BUFFER_SIZE;
			return;
		}
		else if (DMACTL0 & DMA2TSEL_22) {
			__data16_write_addr((unsigned short) &DMA1DA, (unsigned long) buffer);
			DMA2SZ = DMA_BUFFER_SIZE;
			return;
		}
		else {
			return;
		}
		break;
	default:
		return;
	}
}

#ifdef USE_SPI0
#ifdef MSPGCC
__attribute__((interrupt(USCI_A0_VECTOR)))
void _SPIA0_ISR(void) {
#else
#pragma vector=USCI_A0_VECTOR
__interrupt void _SPIA0_ISR(void){
#endif
	SPI_ISR(SPI_A0);
}
#ifdef MSPGCC
__attribute__((interrupt(USCI_B0_VECTOR)))
void DMA_ISR(void) {
#else
#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void) {
#endif
	uint8_t dmaVec = DMAIV;
	SPI_ISR(SPI_A0);
}
#endif

#ifdef USE_SPI1
#ifdef MSPGCC
__attribute__((interrupt(USCI_A1_VECTOR)))
void _SPIA1_ISR(void) {
#else
#pragma vector=USCI_A1_VECTOR
__interrupt void _SPIA1_ISR(void){
#endif
	SPI_ISR(SPI_A1);
}
#ifdef MSPGCC
__attribute__((interrupt(USCI_B0_VECTOR)))
void DMA_ISR(void) {
#else
#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void) {
#endif
	uint8_t dmaVec = DMAIV;
	SPI_ISR(SPI_A1);
}
#endif

#ifdef USE_SPI2
#ifdef MSPGCC
__attribute__((interrupt(USCI_B0_VECTOR)))
void _SPIB0_ISR(void) {
#else
#pragma vector=USCI_B0_VECTOR
__interrupt void _SPIB0_ISR(void){
#endif
	uint8_t dmaVec = DMAIV;
	SPI_ISR(SPI_B0);
}
#ifdef MSPGCC
__attribute__((interrupt(USCI_B0_VECTOR)))
void DMA_ISR(void) {
#else
#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void) {
#endif
	uint8_t dmaVec = DMAIV;
	SPI_ISR(SPI_B0);
}
#endif

#ifdef USE_SPI3
#ifdef MSPGCC
__attribute__((interrupt(USCI_B1_VECTOR)))
void _SPIB1_ISR(void) {
#else
#pragma vector=USCI_B1_VECTOR
__interrupt void _SPIB1_ISR(void){
#endif
	SPI_ISR(SPI_B1);
}
#ifdef MSPGCC
__attribute__((interrupt(USCI_B0_VECTOR)))
void DMA_ISR(void) {
#else
#pragma vector=DMA_VECTOR
__interrupt void DMA_ISR(void) {
#endif
	uint16_t dmaVec = DMAIV;
	SPI_ISR(SPI_B1);
}
#endif

