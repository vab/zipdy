#!/usr/bin/perl

# zipdy.pl
#
# This file is part of Zipdy.
#
# Zipdy is public domain software.

#        Version:        2.5.1
#	 Description:	 This is an example CGI version of 
#			 Zipdy written in perl.
#        Project:        Zipdy: Zip code distance calculator
#        Home:           http://www.cryptnet.net/fsp/zipdy/
#        Author:         V. Alex Brennen <vab@cryptnet.net>
#                        http://www.cryptnet.net/people/vab/


use GDBM_File;
use Math::Trig;

&PostReadParse(*FORM);

print "Content-type: text/html\n\n";
print "<HTML><HEAD><TITLE>Zipdy Results</TITLE></HEAD>\n";
print "<BODY BGCOLOR=#FFFFFF>\n";

tie(%ZIPS, 'GDBM_File', 'zips_gdbm',0,0) || print "err";

	$zip1 = $FORM{'ZIP1'};
	$zip2 = $FORM{'ZIP2'};

	if($zip1 !~ /(\d{5})/)
	{
		print "<H3>Error</H3>Zip code #1 does not appear to be a valid US Zip code.\n";
		exit(0);
	}
	if($zip2 !~ /(\d{5})/)
        {
                print "<H3>Error</H3>Zip code #2 does not appear to be a valid US Zip code.\n";
                exit(0);
        } 

	if(!defined($ZIPS{$zip1}))
	{
		print "<h3>Error</H3>Zip code #1 was not found in the database.\n";
		exit(0);
	}
	if(!defined($ZIPS{$zip2}))
	{
		print "<H3>Error</H3> Zip code #2 was not found in the database.\n";
		exit(0);
	}
	($data1,$trash) = split('\0',$ZIPS{$zip1});
	($data2,$trash) = split('\0',$ZIPS{$zip2});
	($lon1,$lat1) = split(' ',$data1);
	($lon2,$lat2) = split(' ',$data2);

untie(%ZIPS);

	$distance = &great_circle_distance($lon1,$lat1,$lon2,$lat2);

	print "The distance between $zip1 and $zip2 is: $distance miles.\n";

print "</BODY>\n";
print "</HTML>\n";

sub great_circle_distance
{
	local($lon1,$lat1,$lon2,$lat2) = @_;

	# Convert all the degrees to radians
	$lat_1 = &deg_to_rad($lat1);
	$lon_1 = &deg_to_rad($lon1);
	$lat_2 = &deg_to_rad($lat2);
	$lon_2 = &deg_to_rad($lon2);

	# Find the deltas
	$delta_lat = $lat_2 - $lat_1;
	$delta_lon = $lon_2 - $lon_1;

	# Find the Great Circle distance
	$temp = sin($delta_lat/2.0)**2 + cos($lat_1) * cos($lat_2) * sin($delta_lon/2.0)**2;

	# EARTH_RADIUS = 3956

	$distance = 3956 * 2 * atan2(sqrt($temp),sqrt(1-$temp));

	return($distance);
}

sub deg_to_rad
{
	local($deg_2) = @_;
	$radians = 0.0;
	$pi = atan2(1,1) * 4;
	$radians = $deg_2 * $pi/180.0;
	return($radians);
}

sub PostReadParse
{
        local (*in) = @_ if @_;
 
        local($i, $loc, $key, $val);
 
        read(STDIN,$in,$ENV{'CONTENT_LENGTH'});
 
        @in = split(/&/,$in);
 
        foreach $i (0 .. $#in)
        {
        	$in[$i] =~ s/\+/ /g;
 		($key, $val) = split(/=/,$in[$i],2);
 
		$key =~ s/%(..)/pack("c",hex($1))/ge;
		$val =~ s/%(..)/pack("c",hex($1))/ge;
 
		$in{$key} .= "\0" if (defined($in{$key}));
		$in{$key} .= $val; 
        }
	return 1;
} 
