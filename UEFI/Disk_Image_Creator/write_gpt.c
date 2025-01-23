#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>


// -------------- TYPEDEFS --------------------

typedef struct {
	uint8_t bootIndicator;
	uint8_t startingCHS[3];
	uint8_t OS_type;
	uint8_t endingCHS[3];
	uint32_t startingLBA;
	uint32_t size_in_LBAs;
} __attribute__((packed)) MBR_Partition;

typedef struct {
	uint8_t bootCode[440];
	uint32_t MBR_Signature;
	uint16_t unknown;
	MBR_Partition partition[4];
	uint16_t bootSignature;
} __attribute__((packed)) MBR;



// -----------------------------------------------------


// --------------------- CONSTANT DEFINES ---------------------

#ifndef LBA_SIZE
	#define LBA_SIZE 512
#endif

// -------------------------------------------------------------


// ----------------- GLOBAL VARS --------------------------------- 

char *image_name = "test.img";

uint64_t lba_size = LBA_SIZE;
uint64_t esp_size = 1024 * 1024 * 33; // 33MiB (Min size for a FAT32 File System?)
uint64_t data_size = 1024 * 1024 * 1; // 1MiB
uint64_t image_size = 0;
uint64_t esp_lbas = 0;
uint64_t data_lbas = 0;
uint64_t image_lbas = 0;

// -----------------------------------------------------------------

bool write_mbr(FILE *image_file)
{
	uint64_t mbr_image_lbas = image_lbas;
	if(mbr_image_lbas > 0xFFFFFFFF) mbr_image_lbas = 0x100000000;
	MBR mbr = {
		.bootCode = {0},
		.MBR_Signature = 0,
		.unknown = 0,
		.partition[0] = {
			.bootIndicator = 0,
			.startingCHS = {0x00, 0x02, 0x00},
			.OS_type = 0xEE,
			.endingCHS = {0xFF, 0xFF, 0xFF},
			.startingLBA = 0x00000001,
			.size_in_LBAs = mbr_image_lbas - 1
		},
		.bootSignature = 0xAA55,
	};

	if(fwrite(&mbr, 1, sizeof(mbr), image_file) != sizeof(mbr))
	{
		return false;
	}

	return true;
}


static inline uint64_t bytes_to_LBAS(const uint64_t bytes)
{
	return ((bytes + (lba_size - 1)) / lba_size);
	// Equivalent to (bytes / lba_size) + (bytes % lba_size) ? 0 : 1;
	// i.e, add extra LBA in case even if more byte is extra after bytes/lba_size number of LBAS
}

int main()
{

	FILE *image_file = fopen(image_name, "wb+");
	if(!image_file)
	{
		fprintf(stderr, "ERROR: Could not open file %s\n", image_name);
		return EXIT_FAILURE;
	}

	// Set Sizes of Parameters
	image_size = esp_size + data_size + (1024 * 1024); // 1 extra MiB of padding, need to add more padding for the MBR, GPT Headers etc;

	image_lbas = bytes_to_LBAS(image_size);




	if(!write_mbr(image_file))
	{
		fprintf(stderr, "ERROR: Could not write Protective MBR to file %s\n", image_name);
		return EXIT_FAILURE;
	}


	return EXIT_SUCCESS;
}
