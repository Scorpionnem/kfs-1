// definir entrer du programme ( ou est le main)

/* Define the entry point */
ENTRY(_start)

SECTIONS {
	/* The start address */
	. = 2M; 
}


Step 1: Define the entry point 
Step 2: Open the SECTIONS block
Step 3: Define the start address
Step 4: Place the .text section
Step 5: Place the .rodata section
Step 6: Place the .data section
Step 7: Place the .bss section
Step 8: Close the SECTIONS block


Étape 1 : Définir le point d'entrée
Étape 2 : Ouvrir le bloc SECTIONS
Étape 3 : Définir l'adresse de départ
Étape 4 : Placer la section .text
Étape 5 : Placer la section .rodata
Étape 6 : Placer la section .data
Étape 7 : Placer la section .bss
Étape 8 : Fermer le bloc SECTIONS




. 2M -> le linker lis le fichier .ld 
----
OUTPUT_ARCH(i386)
ENTRY(_start)
-----















































/* The bootloader will look at this image and start execution at the symbol
   designated as the entry point. */
ENTRY(_start)


/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* It used to be universally recommended to use 1M as a start offset,
	   as it was effectively guaranteed to be available under BIOS systems.
	   However, UEFI has made things more complicated, and experimental data
	   strongly suggests that 2M is a safer place to load. In 2016, a new
	   feature was introduced to the multiboot2 spec to inform bootloaders
	   that a kernel can be loaded anywhere within a range of addresses and
	   will be able to relocate itself to run from such a loader-selected
	   address, in order to give the loader freedom in selecting a span of
	   memory which is verified to be available by the firmware, in order to
	   work around this issue. This does not use that feature, so 2M was
	   chosen as a safer option than the traditional 1M. */
	. = 2M;

	/* First put the multiboot header, as it is required to be put very early
	   in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

	/* The compiler may produce other sections, by default it will put them in
	   a segment with the same name. Simply add stuff here as needed. */
}