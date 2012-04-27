#!/usr/bin/perl

# convert_to_sql.pl
#
# This file is part of Zipdy.
#
# Zipdy is public domain software.
#

#        Version:        2.0.0
#	 Description:	 This is an text processor to convert
#			 the zipdy data files to SQL.
#        Project:        Zipdy: Zip code distance calculator
#        Home:           http://www.cryptnet.net/fsp/zipdy/
#        Author:         V. Alex Brennen <vab@cryptnet.net>
#                        http://www.cryptnet.net/people/vab/


open(of, ">zipdy_db_load.sql") || die "Couldn't Open Data File w/ Write Permissions!\n";

print "Processing 5 mile radius...\n";

open(df, "five.txt") || die "Couldn't Open Data File!\n";
        while(<df>)
        {
                ($key, $data) = split(/: /, $_);
                chop($data);
                @data_array = split(/ /,$data);
                foreach $zip (@data_array)
                {
                        print of "insert into zips_five values('$key','$zip');\n";
                }

        }
close(df);

print "Processing 10 mile radius...\n";

open(df, "ten.txt") || die "Couldn't Open Data File!\n";
        while(<df>)
        {
                ($key, $data) = split(/: /, $_);
                chop($data);
                @data_array = split(/ /,$data);
                foreach $zip (@data_array)
                {
                        print of "insert into zips_five values('$key','$zip');\n";
                }

        }
close(df);

print "Processing 15 mile radius...\n";

open(df, "fifteen.txt") || die "Couldn't Open Data File!\n";
        while(<df>)
        {
                ($key, $data) = split(/: /, $_);
                chop($data);
                @data_array = split(/ /,$data);
                foreach $zip (@data_array)
                {
                        print of "insert into zips_fifteen values('$key','$zip');\n";
                }

        }
close(df);

print "Processing 20 mile radius...\n";

open(df, "twenty.txt") || die "Couldn't Open Data File!\n";
        while(<df>)
        {
                ($key, $data) = split(/: /, $_);
                chop($data);
                @data_array = split(/ /,$data);
                foreach $zip (@data_array)
                {
                        print of "insert into zips_twenty values('$key','$zip');\n";
                }

        }
close(df);

print "Processing 25 mile radius...\n";

open(df, "twenty_five.txt") || die "Couldn't Open Data File!\n";
        while(<df>)
        {
                ($key, $data) = split(/: /, $_);
                chop($data);
                @data_array = split(/ /,$data);
                foreach $zip (@data_array)
                {
                        print of "insert into zips_twenty_five values('$key','$zip');\n";
                }

        }
close(df);

print "Processing 50 mile radius...\n";

open(df, "fifty.txt") || die "Couldn't Open Data File!\n";
        while(<df>)
        {
                ($key, $data) = split(/: /, $_);
                chop($data);
                @data_array = split(/ /,$data);
                foreach $zip (@data_array)
                {
                        print of "insert into zips_fifty values('$key','$zip');\n";
                }

        }
close(df);

close(of);

print "Finished.\n";
