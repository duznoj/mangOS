1. What is UEFI?
	- Unified Extensible Firemware Interface.
	- An Interface to use firmware APIs (A more modern version of Legacy BIOS and Legacy BIOS Interrupts)
	- The firmware specification given by a group of companies.


2. Why UEFI?
	- UEFI is only a specification with many implementations such as AMI Aptio, Phoenix SecureCOre, TinaCore EDK II, etc.
	- A "UEFI Application" is a software that the firmware on the motherboard will recognize, the UEFI Application makes use of the UEFI API to perform tasks on the hardware in a pre-OS environment, so modern bootloaders for OS should be written as an UEFI Application


3. Goal for this project:
	- End up with a bootloader which is UEFI compatible, and end up in an OS kernel in C with full CPU capabilites, i.e 64-Bit Long Mode


4. Requirements:
	1. UEFI Spec is language agnostic, but since most of the implementations are made in C, we'll write out Bootloader in C (and ofc cuz C is the greatest language if all time)

	2. A UEFI App must be in the form of a Windows Executable, i.e the PE32+ (Portable Executable) formant, so we use the mingw-64 bit cross compiler for the final UEFI App.

	3. The Creation of a raw partition table (GPT = GUID Partition Table) for the bootable disk however does not depend on the PE32+ or ELF formats, its a raw bianry, so that can be created from any C Compiler.

	4. qemu for testing.

	5. A UEFI Firmware Emulator (OVMF = Open Virtual Machine Firmware)
	
	6. A program which writes a raw and valid GPT disk image and bakes the UEFI Application into it

	7. Any utility to copy the disk image to a USB Flash Drive (dd on Linux)

	8. "gdisk" utility software to verify whether the Disk Image we wrote is valid or not, maybe could be alternatively be done by "file" command
