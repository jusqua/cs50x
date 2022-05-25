#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define RANGE 512
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // Usage string
    const char *usage = "Usage: ./recover image";
    if (argc == 2)
    {
        // Open file
        FILE *inptr = fopen(argv[1], "r");
        // If does not exist, show usage, close app
        if (inptr == NULL)
        {
            puts(usage);
            return 1;
        }
        // Initializing variables
        FILE *outptr;
        BYTE buffer[512];
        int filecount = 0;
        char filename[8];
        // Read until remains nothing
        while (fread(buffer, sizeof(BYTE), RANGE, inptr))
        {
            // Check if is a JPEG header
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // If already found a JPEG header, close file
                if (filecount > 0)
                {
                    fclose(outptr);
                }
                // Set file name
                sprintf(filename, "%03i.jpg", filecount);
                // Open new file
                outptr = fopen(filename, "w");
                // Write data
                fwrite(buffer, sizeof(BYTE), RANGE, outptr);
                filecount++;
            }
            // Else if already found a JPEG header
            else if (filecount)
            {
                // Write data
                fwrite(buffer, sizeof(BYTE), RANGE, outptr);
            }
        };
        fclose(outptr);
        fclose(inptr);
        return 0;
    }
    // Usage
    else
    {
        puts(usage);
        return 1;
    }
}