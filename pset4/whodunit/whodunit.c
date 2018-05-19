#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"


int
main(int argc, char *argv[])
{
    //VALIDATE THE COMMAND ARGUMENTS
    if (argc != 3)
    {
        fprintf (stderr, "ONLY TWO COMAND ARGUMENT!\n");
        return 1;
    }

    // OPEN THE INPUT FILE 
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf("CANNNOT OPEN %s.\n", argv[1]);
        return 2;
    }

    //CREATE THE OUTPUT FILE
    FILE *outptr = fopen(argv[2], "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "CANNOT CREATTE %s.\n", argv[2]);
        return 2;
    }

    //READ INFILE BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    //READ INFILE BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    //VALIDATE THE 24-BIT UNCOMPRESSED BMP 4.0 FILE
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //WRITE OUTFILE BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    //WRITE OUTFILE BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    //DETERMINATE PADDING FOR SCALE LINES
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            RGBTRIPLE triple;

 S           fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            if (triple.rgbtRed == 0xff)
                triple.rgbtRed = 0x00;
            if (triple.rgbtBlue == 0xff)
                triple.rgbtBlue = 0x00;
            if (triple.rgbtGreen == 0xff)
                triple.rgbtGreen = 0x00;

            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        fseek(inptr, padding, SEEK_CUR);

        for (int k = 0; k < padding; k++)
            fputc(0x00, outptr);
    }

    fclose(inptr);
    fclose(outptr);

    return 0;
}