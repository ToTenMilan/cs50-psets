/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    // don't accept any cmd-line arguments
    if (argc != 1)
    {
        printf("run by typing just a name of the program\n");
        return 1;
    }
    
    // open "card.raw"  
    FILE* mc = fopen("card.raw", "r");
    if (mc == NULL)
    {
        return 1;
    }
    
    // initialize file pointer
    FILE* image = NULL;
    
    // initialize buffer
    uint8_t buffer[512];
    
    // initialize counter for images
    int ctr = 0;
    
    // initialize temporary array for filenames
    char filename[10];
    
    //repeat until eof
    while (fread(buffer, 1, 512, mc) == 512)
    {
        // start for new jpg?
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
                // (buffer[3] >= 0xe0 || buffer[3] <= 0xef)
        {
            // yes... (close current jpg and open new)
            if (ctr != 0)
            {
                fclose(image);
            }   
            // create new jpg
            sprintf(filename, "%03d.jpg", ctr);
            image = fopen(filename, "w");
            
            // print first four bytes
            // printf("1st B of %02d: %d | %d | %d | %d\n", ctr, buffer[0], buffer[1], buffer[2], buffer[3]);
            ctr++;
        }
        // if jpg already found, write to it
        if (ctr != 0)
        {           
            fwrite(buffer, 1, 512, image);
        }
        // last read should be different than 512B
        // if(fread(buffer, 1, 512, mc) != 512)
        // {
        //     feof(mc);
        // }
    }
    
    fclose(image);
    fclose(mc);
}