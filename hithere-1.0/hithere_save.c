
#include "ftdi.h"

#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

//#define PH0        224    // (32 * 7) + 0
//#define PH2        226    // (32 * 7) + 2

//#define GPIO_PATH  "/sys/class/gpio/gpio224/value"
//#define GPIO_PATH  "/sys/class/gpio/gpio226/value"

int main() {
	printf("led driver\n");

	/*
	int counter = 10000;
	int ret;
	int fd;

	fd = open(GPIO_PATH, O_RDWR);
	if (fd < 0){
		printf("could not open file\n");
		return errno;
	}

	while(1){
		counter = 665000;
		printf("set\n");
		while(counter-->0) {
			ret = write(fd, "1", 1);
		}
		counter = 665000;
		printf("clear\n");
		while(counter-->0){
			ret = write(fd, "0", 1);
		}
	}
	return 0;
	*/

	int ret;
	struct ftdi_context *ftdi;
	struct ftdi_version_info version;
	if ((ftdi = ftdi_new()) == 0)
	{
		fprintf(stderr, "ftdi_new failed\n");
		return 1;
	}

	version = ftdi_get_library_version();
	printf("Initialized libftdi %s (major: %d, minor: %d, micro: %d, snapshot ver: %s)\n",
	version.version_str, version.major, version.minor, version.micro,
	version.snapshot_str);

	if ((ret = ftdi_usb_open(ftdi, 0x0403, 0x6010)) < 0){
		fprintf(stderr, "unable to open ftdi device: %d (%s)\n", ret, ftdi_get_error_string(ftdi));
		ftdi_free(ftdi);
		return 1;
	}
	else {
		printf("found module\n");


    printf("enabling bitbang mode\n");
    ftdi_set_bitmode(ftdi, 0xFF, BITMODE_BITBANG);

	usleep(3 * 1000000);
    int f,i;
    unsigned char buf[1];

    buf[0] = 0x0;
    printf("turning everything on\n");
    f = ftdi_write_data(ftdi, buf, 1);
    if (f < 0)
    {
        fprintf(stderr,"write failed for 0x%x, error %d (%s)\n",buf[0],f, ftdi_get_error_string(ftdi));
    }

    usleep(3 * 1000000);


        buf[0] = 0xFF;
	printf("turning everything off\n");
    f = ftdi_write_data(ftdi, buf, 1);
    if (f < 0)
    {
        fprintf(stderr,"write failed for 0x%x, error %d (%s)\n",buf[0],f, ftdi_get_error_string(ftdi));
    }

    usleep(3 * 1000000);

    for (i = 0; i < 32; i++)
    {
        buf[0] =  0 | (0xFF ^ 1 << (i % 8));
        if ( i > 0 && (i % 8) == 0)
        {
            printf("\n");
        }
        printf("%02hhx ",buf[0]);
        fflush(stdout);
        f = ftdi_write_data(ftdi, buf, 1);
        if (f < 0)
        {
            fprintf(stderr,"write failed for 0x%x, error %d (%s)\n",buf[0],f, ftdi_get_error_string(ftdi));
        }
        usleep(1 * 1000000);
    }
	}
 
	if ((ret = ftdi_usb_close(ftdi)) < 0){
		fprintf(stderr, "unable to close ftdi device: %d (%s)\n", ret, ftdi_get_error_string(ftdi));
		ftdi_free(ftdi);
		return 1;
	}

	ftdi_free(ftdi);
	return 0;
}
