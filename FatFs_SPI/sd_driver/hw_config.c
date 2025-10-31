/* hw_config.c - Hardware configuration for SD card on Pico Pi Maker
 * This file configures the FatFS library for your specific hardware setup
 * 
 * Place this in: no-OS-FatFS-SD-SPI-RPi-Pico/FatFs_SPI/sd_driver/hw_config.c
 */

#include "hw_config.h"
#include <limits.h>

// Hardware Configuration of SPI "objects"
static spi_t spis[] = {
    {
        .hw_inst = spi1,  // Using SPI1 for SD card (SPI0 is for your flash chip)
        .miso_gpio = 12,  // DAT0/MISO on GP12
        .mosi_gpio = 11,  // CMD/MOSI on GP11
        .sck_gpio = 10,   // CLK on GP10
        .baud_rate = 12500 * 1000,  // 12.5 MHz
        .DMA_IRQ_num = DMA_IRQ_0,
    }
};

// Hardware Configuration of the SD Card "objects"
static sd_card_t sd_cards[] = {
    {
        .pcName = "0:",       // Name used to mount the SD card
        .spi = &spis[0],      // Pointer to the SPI config above
        .ss_gpio = 15,        // CS pin on GP15 (CD/DAT3)
        
        // Card detect pin (optional)
        .use_card_detect = false,
        .card_detect_gpio = UINT_MAX,
        .card_detected_true = -1,
    }
};

// Function called by FatFS library to get SPI configuration
size_t spi_get_num() { 
    return count_of(spis); 
}

spi_t *spi_get_by_num(size_t num) {
    if (num < count_of(spis)) {
        return &spis[num];
    }
    return NULL;
}

// Function called by FatFS library to get SD card configuration
size_t sd_get_num() { 
    return count_of(sd_cards); 
}

sd_card_t *sd_get_by_num(size_t num) {
    if (num < count_of(sd_cards)) {
        return &sd_cards[num];
    }
    return NULL;
}