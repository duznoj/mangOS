						------------- INTRO -------------

Why GPT?
	- Legacy BIOS, i.e ending the first sector od Hard Disk with 0xAA55 will no longer be enough to identify the boot device by the UEFI firmware.

	- While currently UEFI is backwards compatible with Legavy BIOS via the Master Boot Reacord (MBR) which is basically again the first sector ending with 0xAA55, but Intel is going to end Hardware Support for Legacy BIOS, so better to shift to UEFI.


Modern UEFI will find your Bootloader iff the boot device has an EFI System Partition (ESP) which is a FAT32 Partition, and at least has the file /EFI/BOOT/BOOTx64.EFI.

So our "write-gpt" will write the Disk Image which includes:
	1. Protective MBR (Backwards Compatibilty for Legacy BIOS)

	2. Primary and Secondary GPT Headers

	3. Primary and Secondary GPT Parttiion entry arrays

	4. The ESP

The "write_gpt" is a portable program which will generate a valid Disk Image when compiled and run on any platform.

					----------------------------------------------------


Sections below will only have a brief overview, checkout the UEFI Spec documentation for implementation details



					------------------ MAIN CONTENT/LOGIC -----------------

[ ] Write LBA 0 protective MBR, with 0xEE as OS Type
	


