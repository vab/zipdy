/* gdbm_create.c
 *
 * This file is part of Zipdy.
 *
 * Zipdy is public domain software.
 */

/*
        Version:        2.5.1
	Description:	This program creates a GDBM database
			of zip code information from the text
			data file.
        Project:        Zipdy: Zip code distance calculator
        Home:           http://www.cryptnet.net/fsp/zipdy/
        Author:         V. Alex Brennen <vab@cryptnet.net>
                        http://www.cryptnet.net/people/vab/
*/

#include <stdio.h>
#include <gdbm.h>

int main(void)
{
        FILE  *data_file;
        char  line[80];
        char  buffer[80];

        GDBM_FILE dbf;
        int ret;

        datum  data;
        datum  info;

        char    zip[6];
        float   lng;
        float   lat;

        if( (data_file = fopen("zip_loc.txt", "r")) == NULL)
        {
                printf("Error Couldn't open zips data file\n");
                exit(1);
        }

        if( (dbf = gdbm_open("zips_gdbm",1024,GDBM_NEWDB, 0755, 0)) == NULL)
	{
		fprintf(stderr, "Error: Couldn't open GDBM out file.");
		exit(1);
	}

        while(!feof(data_file))
        {
                fgets(line,80,data_file);
                sscanf(line,"%s %f %f", &zip, &lng, &lat);
                data.dptr = zip;
                data.dsize = 5;
                sprintf(buffer,"%f %f", lng, lat);
                info.dptr = buffer;
                info.dsize = 80;
                gdbm_store(dbf,data,info,GDBM_INSERT);
        }

        fclose(data_file);
        gdbm_close(dbf);

	printf("GDBM Database Created.\n");

        exit(0);
}
