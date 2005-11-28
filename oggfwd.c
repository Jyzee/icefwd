/* example.c: Demonstration of the libshout API. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shout/shout.h>

int main(argc,argv)
int argc;
char *argv[];
{
	shout_t *shout;
	char buff[4096];
	long read, ret, total;

	if (!(shout = shout_new())) {
		printf("Could not allocate shout_t\n");
		return 1;
	}

	if(argc != 5) {
		puts("usage: oggfwd hostname port# password target\nsample: oggfwd icecast.v2v.cc 8000 password /theora.ogg");
		exit(-1);
	}
	if (shout_set_host(shout, argv[1]) != SHOUTERR_SUCCESS) {
		printf("Error setting hostname: %s\n", shout_get_error(shout));
		return 1;
	}
	shout_set_port(shout, atoi(argv[2]));
	if (shout_set_password(shout, argv[3]) != SHOUTERR_SUCCESS) {
		printf("Error setting password: %s\n", shout_get_error(shout));
		return 1;
	}
	if (shout_set_mount(shout, argv[4]) != SHOUTERR_SUCCESS) {
		printf("Error setting mount: %s\n", shout_get_error(shout));
		return 1;
	}
	shout_set_format(shout, SHOUT_FORMAT_VORBIS);

	if (shout_open(shout) == SHOUTERR_SUCCESS) {
		printf("Connected to server...\n");
		total = 0;
		while (1) {
			read = fread(buff, 1, sizeof(buff), stdin);
			total = total + read;

			if (read > 0) {
				ret = shout_send(shout, buff, read);
				if (ret != SHOUTERR_SUCCESS) {
					printf("DEBUG: Send error: %s\n", shout_get_error(shout));
					break;
				}
			} else {
				break;
			}

			shout_sync(shout);
		}
	} else {
		printf("Error connecting: %s\n", shout_get_error(shout));
	}

	shout_close(shout);

	return 0;
}
