/* main.c
   Output some flickering in bitbang mode to the FT2232
   This program is distributed under the GPL, version 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ftdi.h>

int main(int argc, char **argv) {
	struct ftdi_context *ftdi;
	unsigned char buf[1];
	int f,i;

	printf("init interface A\n")
	if ((ftdi = ftdi_new()) == 0) {
		fprintf(stderr, "ftdi_new failed\n");
		return EXIT_FAILURE;
	}

	ftdi_set_interface(ftdi, INTERFACE_A);
	f = ftdi_usb_open(ftdi, 0x0403, 0x6010);
	if (f < 0 && f != -5) {
		fprintf(stderr, "unable to open ftdi device: %d (%s)\n", f, ftdi_get_error_string(ftdi));
		ftdi_free(ftdi);
		exit(-1);
	}
	printf("ftdi open succeeded(channel 1): %d\n",f);

	printf("enabling bitbang mode(channel 1)\n");
	ftdi_set_bitmode(ftdi, 0xFF, BITMODE_BITBANG);

	// Write data
	printf("startloop\n");
	while(1){
		// loop over all 3 colors outputs (lowest 3 bits)
		for (i = 0b0001; i <= 0b0111; i++){
			buf[0] =  i<<4;
			printf("porta: %02i: 0x%02x \n",i,buf[0]);
			f = ftdi_write_data(ftdi, buf, 1);
			if (f < 0)
			fprintf(stderr,"write failed on channel 1 for 0x%x, error %d (%s)\n", 
					buf[0], f, ftdi_get_error_string(ftdi));
			usleep(1 * 1000000);

			buf[0] =  0x00;
			printf("porta: %02i: 0x%02x \n",i,buf[0]);
			f = ftdi_write_data(ftdi, buf, 1);
			if (f < 0)
			fprintf(stderr,"write failed on channel 1 for 0x%x, error %d (%s)\n", 
					buf[0], f, ftdi_get_error_string(ftdi));
			usleep(1 * 1000000);
		}
	}
	printf("\n");

	printf("disabling bitbang mode(channel 1)\n");
	ftdi_disable_bitbang(ftdi);
	ftdi_usb_close(ftdi);
	ftdi_free(ftdi);

	return 0;
}
