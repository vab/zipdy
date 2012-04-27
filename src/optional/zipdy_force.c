/* zipdy_force.c
 *
 * This file is part of Zipdy.
 *
 * Zipdy is public domain software.
 */

/*
	Version:	2.0.0
	Description:	This program creates a number of GDBM
			databases which list zip codes with
			in a radius of another zip code.
        Project:        Zipdy: Zip code distance calculator
	Home:		http://www.cryptnet.net/fsp/zipdy/
	Author:		V. Alex Brennen <vab@cryptnet.net>
			http://www.cryptnet.net/people/vab/
*/

#include <stdio.h>
#include <gdbm.h>
#include <math.h>

/* Radius of the earth in miles */
#define EARTH_RADIUS 3956

float great_circle_distance(float lat1,float long1,float lat2,float long2);
float deg_to_rad(float deg);

int main(void)
{
        GDBM_FILE       dbf;
	GDBM_FILE	dbf2;
        int             result;

	FILE		*five;
	FILE		*ten;
	FILE		*fifteen;
	FILE		*twenty;
	FILE		*twenty_five;
	FILE		*fifty;

        datum           data;
        datum           info;
        datum           data2;

	datum		data3;
	datum		info3;
	datum		data4;

        float           lat1;
        float           lon1;
        float           lat2;
        float           lon2;

        float           distance;

	char		buff[10];

        if((dbf = gdbm_open("zips_gdbm",1024,GDBM_READER, 0755, 0)) ==NULL)
        {
                fprintf(stderr, "Unable to open gdbm data file.\n");
                exit(1);
        }

	if((dbf2 = gdbm_open("zips_gdbm_2",1024,GDBM_READER,0755,0)) ==NULL)
	{
		fprintf(stderr, "Unable to open second gdbm data file.\n");
		exit(1);
	}

	if((five = fopen("five.txt","w")) == NULL)
	{
		fprintf(stderr, "Unable to open 5 mi. out file.\n");
		exit(1);
	}

	if((ten = fopen("ten.txt","w")) == NULL)
        {
                fprintf(stderr, "Unable to open 10 mi. out file.\n");
                exit(1);
        }

	if((fifteen = fopen("fifteen.txt","w")) == NULL)
        {
                fprintf(stderr, "Unable to open 15 mi. out file.\n");
                exit(1);
        }

	if((twenty = fopen("twenty.txt","w")) == NULL)
        {
                fprintf(stderr, "Unable to open 20 mi. out file.\n");
                exit(1);
        }

	if((twenty_five = fopen("twenty_five.txt","w")) == NULL)
        {
                fprintf(stderr, "Unable to open 25 mi. out file.\n");
                exit(1);
        }

	if((fifty = fopen("fifty.txt","w")) == NULL)
        {
                fprintf(stderr, "Unable to open 50 mi. out file.\n");
                exit(1);
        }
	printf("Processing...\n");
	data = gdbm_firstkey(dbf);

	while(data.dptr)
	{
		data2 = gdbm_nextkey(dbf,data);
		info = gdbm_fetch(dbf,data);
        	sscanf(info.dptr,"%f%f",&lon1, &lat1);
		sprintf(buff,"%s",data.dptr);
		buff[5] = '\0';
		printf("Testing Zip Code: %s\n", buff); 

		fprintf(five,"%s:",buff);
		fprintf(ten,"%s:", buff);
		fprintf(fifteen,"%s:",buff);
		fprintf(twenty,"%s:", buff);
		fprintf(twenty_five,"%s:",buff);
		fprintf(fifty, "%s:",buff);

		free(data.dptr);
		free(info.dptr);

		data = data2;

		data3 = gdbm_firstkey(dbf2);
		while(data3.dptr)
		{
			data4 = gdbm_nextkey(dbf2,data3);
       	        	info3 = gdbm_fetch(dbf2,data3);
       	        	sscanf(info3.dptr,"%f%f",&lon2,&lat2);
       	        	distance = great_circle_distance(lat1,lon1,lat2,lon2);
			data3.dptr[5] = '\0';
		
			if(distance <= 5)
			{
				fprintf(five, " %s", data3.dptr);
			}
			if(distance <= 10)
			{
				fprintf(ten, " %s", data3.dptr);
			}
			if(distance <= 15)
			{
				fprintf(fifteen, " %s",data3.dptr);
			}
			if(distance <= 20)
			{
				fprintf(twenty, " %s",data3.dptr);
			}
			if(distance <= 25)
			{
				fprintf(twenty_five," %s",data3.dptr);
			}
			if(distance <= 50)
			{
				fprintf(fifty," %s",data3.dptr);
			}

			free(data3.dptr);	
			free(info3.dptr);

			data3 = data4;
		}
                fprintf(five,"\n",buff);
                fprintf(ten,"\n",buff);
                fprintf(fifteen,"\n",buff);
                fprintf(twenty,"\n",buff);
                fprintf(twenty_five,"\n",buff);
                fprintf(fifty,"\n",buff);
	}

	fclose(five);
	fclose(ten);
	fclose(fifteen);
	fclose(twenty);
	fclose(twenty_five);
	fclose(fifty);

        gdbm_close(dbf);
	gdbm_close(dbf2);

	printf("Finished.\n");

        return 0;
}

float great_circle_distance(float lat1,float long1,float lat2,float long2)
{
        float delta_long = 0;
        float delta_lat = 0;
        float temp = 0;
        float distance = 0;

        /* Convert all the degrees to radians */
        lat1 = deg_to_rad(lat1);
        long1 = deg_to_rad(long1);
        lat2 = deg_to_rad(lat2);
        long2 = deg_to_rad(long2);

        /* Find the deltas */
        delta_lat = lat2 - lat1;
        delta_long = long2 - long1;

        /* Find the GC distance */
        temp = pow(sin(delta_lat / 2.0), 2) + cos(lat1) * cos(lat2) * pow(sin(delta_long / 2.0), 2);

        distance = EARTH_RADIUS * 2 * atan2(sqrt(temp),sqrt(1 - temp));

        return (distance);
}

float deg_to_rad(float deg)
{
        double radians = 0;

        radians = deg * M_PI / 180.0;

        return(radians);
}
