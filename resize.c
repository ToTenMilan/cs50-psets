/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
 
int main(int argc, char* argv[])
{
    // convert argv[1] to int
    int n = atoi(argv[1]);
    int* pn = &n;
    // ensure proper usage
    if (argc != 4 || (*pn < 1 || *pn > 100))
    {
        printf("Usage: ./resize n(1..100) infile outfile\n");
        return 1;
    }
 
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }
 
    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
 
    // read infile's BITMAPFILEHEADER
                        // BITMAPFILEHEADER bf;
    BITMAPFILEHEADER* pbf = NULL;
    pbf = malloc(sizeof(BITMAPFILEHEADER));
    if (pbf == NULL)
    {
        printf("not enough memory");
        return 2;
    }
                        // *pbf = bf;
                        // BITMAPFILEHEADER* pbfNew = malloc(sizeof(BITMAPFILEHEADER));
    BITMAPFILEHEADER* pbfNew = NULL;
    pbfNew = malloc(sizeof(BITMAPFILEHEADER));
    if (pbfNew == NULL)
    {
        printf("not enough memory");
        return 2;
    }
    fread(pbf, sizeof(BITMAPFILEHEADER), 1, inptr);
    // read infile's BITMAPINFOHEADER
                        // BITMAPINFOHEADER bi;
    BITMAPINFOHEADER* pbi = NULL;
    pbi = malloc(sizeof(BITMAPINFOHEADER));
    if (pbi == NULL)
    {
        printf("not enough memory");
        return 2;
    }
                        // *pbi = bi;
                        // BITMAPINFOHEADER* pbiNew = malloc(sizeof(BITMAPINFOHEADER)); 
    BITMAPINFOHEADER* pbiNew = NULL;
    pbiNew = malloc(sizeof(BITMAPINFOHEADER));
    if (pbiNew == NULL)
    {
        printf("not enough memory");
        return 2;
    }
    fread(pbi, sizeof(BITMAPINFOHEADER), 1, inptr);
 
                        // printf("Location: %d\n", pbf->bfType); 
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (pbf->bfType != 0x4d42 || pbf->bfOffBits != 54 || pbi->biSize != 40 ||
        pbi->biBitCount != 24 || pbi->biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
   
    *pbfNew = *pbf;
    *pbiNew = *pbi;
   
    pbiNew->biWidth = pbi->biWidth * *pn;
    pbiNew->biHeight = pbi->biHeight * *pn;
    int paddingNew =  (4 - (pbiNew->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    pbiNew->biSizeImage = (pbiNew->biWidth * abs(pbiNew->biHeight) * sizeof(RGBTRIPLE)) + (paddingNew * abs(pbiNew->biHeight));
    pbfNew->bfSize = sizeof(*pbf) + sizeof(*pbi) + pbiNew->biSizeImage;
 
    // write outfile's BITMAPFILEHEADER
    fwrite(pbfNew, sizeof(BITMAPFILEHEADER), 1, outptr);
 
    // write outfile's BITMAPINFOHEADER
    fwrite(pbiNew, sizeof(BITMAPINFOHEADER), 1, outptr);
 
    // determine padding for scanlines
    int padding =  (4 - (pbi->biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
 
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(pbi->biHeight); i < biHeight; i++)
    {
        for (int v = 0; v < *pn; v++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < (pbi->biWidth); j++)
            {
                // temporary storage
                RGBTRIPLE triple;
   
                // read RGBTRIPLE from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
               
                // write pixel every n times horizontally
                for (int y = 0; y < n; y++)
                {
                    fwrite(&triple, (sizeof(RGBTRIPLE)), 1, outptr);
                }
            }
            fseek(inptr, padding, SEEK_CUR);
            
            // add padding to horizontal line in outfile
            for (int z = 0; z < paddingNew; z++)
            {
                fputc(0x00, outptr);
            }
            fseek(inptr, -(int)((pbi->biWidth * sizeof(RGBTRIPLE)) + padding), SEEK_CUR);
        }
        fseek(inptr, ((pbi->biWidth * sizeof(RGBTRIPLE)) + padding), SEEK_CUR);
    }
    
    free(pbf);
    free(pbi);
    free(pbfNew);
    free(pbiNew);
 
    // close infile
    fclose(inptr);
 
    // close outfile
    fclose(outptr);
 
    // that's all folks
    return 0;
}
