#include <stdio.h>
#include <stdlib.h>

void encode_files(int file_count, char *file_paths[]) {
    int current_character = EOF;
    int previous_char = EOF;
    unsigned char count = 0;

    for (int i = 0; i < file_count; i++) {
        FILE *input_file = fopen(file_paths[i], "rb");
        if (!input_file) {
            // fprintf(stderr, "Error: '%s'\n", file_paths[i]);
            continue;
        }

        while ((current_character = fgetc(input_file)) != EOF) {
            if (current_character == previous_char) {
                count++;
                if (count == 255) {
                    fwrite(&previous_char, 1, 1, stdout);
                    fwrite(&count, 1, 1, stdout);
                    count = 0;
                }
            } else {
                if (previous_char != EOF) {
                    fwrite(&previous_char, 1, 1, stdout);
                    fwrite(&count, 1, 1, stdout);
                }
                previous_char = current_character;
                count = 1;
            }
        }
        fclose(input_file);
    }

    if (previous_char != EOF) {
        fwrite(&previous_char, 1, 1, stdout);
        fwrite(&count, 1, 1, stdout);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    encode_files(argc - 1, &argv[1]);
    return 0;
}
