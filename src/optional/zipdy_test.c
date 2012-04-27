/* zipdy_test.c
 *
 * This file is part of Zipdy.
 *
 * Zipdy is public domain software.
 */

/*
        Version:        2.0.0
	Description:	This program was written to allow you
			to test the GIS calcs in zipdy on your
			system.
        Project:        Zipdy: Zip code distance calculator
        Home:           http://www.cryptnet.net/fsp/zipdy/
        Author:         V. Alex Brennen <vab@cryptnet.net>
                        http://www.cryptnet.net/people/vab/
*/

#include <stdio.h>
#include <math.h>
#include <gdbm.h>

/* Radius of the earth in miles */
#define EARTH_RADIUS 3956

float great_circle_distance(float lat1,float long1,float lat2,float long2);
float deg_to_rad(float deg);

int main(void)
{
        GDBM_FILE       dbf;
        int             result;

        datum           data;
        datum           info;
	datum		data2;
	datum		info2;

	float		lat1;
	float		lon1;
	float		lat2;
	float		lon2;

	float		distance;

        if((dbf = gdbm_open("zips_gdbm",1024,GDBM_READER, 0755, 0)) ==NULL)
	{
		fprintf(stderr, "Unable to open gdbm data file.\n");
		exit(1);
	}

        data.dptr = "32601";
        data.dsize = 5;
        info = gdbm_fetch(dbf,data);
	sscanf(info.dptr,"%f%f",&lon1, &lat1);

        free(info.dptr);

	data2.dptr = "60477";
	data2.dsize = 5;
	info2 = gdbm_fetch(dbf,data2);
        sscanf(info2.dptr,"%f%f",&lon2,&lat2);

        free(info2.dptr);

	distance = great_circle_distance(lat1,lon1,lat2,lon2);	
	printf("Calculated Distance: %f\n\n", distance);
	printf("The calculated distance should be: 916.705139 miles.\n");

        gdbm_close(dbf);
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
