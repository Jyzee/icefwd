/* oggfwd.c: A very useful demonstration of the libshout API, by J <j@v2v.cc> */
/* some improvements by -- rafael2k <rafael (AT) riseup (DOT) net> */
/* thanx to rhatto <rhatto (AT) riseup (DOT) net> and others at submidialogia :-P   */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <shout/shout.h>

int main(int argc, char **argv) {
	shout_t *shout;
	unsigned char buff[4096];
	long read, ret, total;

	if (!(shout = shout_new())) {
		printf("Could not allocate shout_t\n");
		return 1;
	}

	if(argc != 5 && argc != 11) {
	  puts("oggfwd\n\n" 
	       "|| Simple Usage: ||\n" 
	       " oggfwd server_address port_number password target\n"
	       "Sample:\n oggfwd icecast.v2v.cc 8000 password /theora.ogg\n"
	       "\n\n"
	       "|| Advanced Usage: ||\n"
	       "Use strings (a single word or a \"w o r d\" with spaces, inside \" \" ) or use the\npossible values available inside the parentheses: -> 0 means False | 1 means True <-\n\n"
	       "Command Format:\n oggfwd server_address port_number password mount_point radio_name url genre description set_public(0,1) dump_file(0,dump_file_name) \n\n"
	       "Sample:\n oggfwd orelhao.radiolivre.org 8100 secret_password /mount_point.ogg \"Radio Freak\" http://doidos.radiolivre.org/ free_style \"A Radio dos doid@s\" 1 /tmp/dumpfile.ogg \n\n");
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
	
	/* Advanced options */
	if (argc == 11) {
	  
	  shout_set_name(shout, argv[5]);

	  shout_set_url(shout,argv[6]);

	  shout_set_genre(shout, argv[7]);

	  shout_set_description(shout, argv[8]);

	  shout_set_public(shout, atoi(argv[9]));

	  if (strncmp(argv[10], "0", 1)) 
	    shout_set_dumpfile(shout, argv[10]);
	}

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
