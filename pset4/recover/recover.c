
 #include <stdio.h>
 #include <stdint.h>
 
 const int BLOCK_SIZE = 512;
 
 int main(int argc, char *agrv[])
 {
     
    //VALIDATE THE NUMBER OF COMMAND ARGUMENTS
 	if(argc != 2)
    {
        fprintf (stderr, "ONLY ONE COMAND ARGUMENT!\n");
        return 1;
    }
 	
 	//CREATE THE FILE FOR WRITTEN
    FILE* f= fopen(agrv[1], "r");
    
    //VALIDATE THAT THE FILE`S CREATION HAPPENS WELL
    if (f == NULL)
    {
        fprintf(stderr,"Error opening the file\n");
        return 2;
    }
    
    //CREATE THE BUFFER
    uint8_t buf[512];
    
    int counter = 0;
    FILE *fw = NULL;
    
    while (fread(buf, BLOCK_SIZE, 1, f))
    {
        //CHECK THA JPG FORMAT
        if (buf[0] == 0xff && buf[1] == 0xd8 && buf[2] == 0xff
            && (buf[3] == 0xe0 || buf[3] == 0xe1 || buf[3] == 0xe2 
            || buf[3] == 0xe3 || buf[3] == 0xe4 || buf[3] == 0xe5 
            || buf[3] == 0xe6 || buf[3] == 0xe7 || buf[3] == 0xe8 
            || buf[3] == 0xe9 || buf[3] == 0xea || buf[3] == 0xeb
            || buf[3] == 0xec || buf[3] == 0xed || buf[3] == 0xee 
            || buf[3] == 0xef))
        {
            //CLOSE THE FILE IF IS OPEN
            if (fw != NULL)
                fclose(fw);
            
            char filename[8];
            sprintf(filename, "%03d.jpg", counter);
                
            //OPEN JPG FILE FOR WRITTING, FOR THE NEW ITERATION
            fw = fopen(filename, "w");
            
            counter++;
        }
        
        if (fw != NULL)
            fwrite(buf, BLOCK_SIZE, 1, fw);
    }
    
    //CLOSE THE FILE IF IS OPEN
    if (fw != NULL)
        fclose(fw);
    
    //ALWAYS CLOSE A FILE
    fclose(f);
 
    return 0;
 } 