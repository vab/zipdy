#!/usr/bin/perl

# This script separates the zip code, longitude, and latitude, values from 
# the zip code file distributed by the US Census.

# 00601   166659789       799296  64.348  0.309   -66.749961      18.180555

open(ZIPS,"zips.txt") || die "failed to open Zip File.\n";
	while(<ZIPS>)
	{
		($zip,$trash,$trash,$trash,$trash,$long,$lat) = split(/\s+/,$_);
		print "$zip $long $lat\n";
	}
close(ZIPS);

