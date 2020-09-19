// From Puzzles for Hackers
#include <stdio.h>
#include <string.h> 

int main (int argc, char *argv[]) {
	FILE *in, *out;
	char *key;
	int byte;

	if (argc !=4) {
		printf ("Usage: xor <key> <input_file> <output_file>\n");
		return 1;
	}

	key = argv[1];

	// Used to demo reversability of XOR encryption. Encr form of alphabet encoded with FISH as key.
	char keyF[] = {0x07, 0x0B, 0x10, 0x0C, 0x03, 0x0F, 0x14, 0x00, 0x0F, 0x03, 0x18, 0x04, 0x0B};
	int keyF_SIZE = 13;


	if ((in = fopen(argv[2], "rb")) != NULL) {
		if ((out = fopen(argv[3], "wb")) != NULL) {

			int idx = 0;
			int rawcount = 0;
			char q;
			while ((byte = getc(in)) != EOF) {
				if (strcmp(key, "42") == 0) {
					// do fixed key version
					byte ^= keyF[idx++];
					q = byte;
					putc(byte,out);
					if (idx == keyF_SIZE)
						idx = 0;
					rawcount++;
				}
				else {
					// do 'standard' version.
					// The following line determines if key pointer is pointing at null. 
					//   if it is, it repoints key to the beginning of the argv[1] string.
					if (!*key) {
						key = argv[1]; 
					}
					byte ^= *(key++);
					putc(byte,out);

				}
			}

			fclose(out); 
		} 

		fclose(in); 
	}

	return 0;
}
