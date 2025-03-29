<HTML><HEAD><TITLE>Zipdy Results</TITLE></HEAD>
<BODY BGCOLOR=#FFFFFF>
<?
/* zipdy.php
 *
 * Zipdy is public domain software.
 */


/*
        Version:        2.5.1
	Description:	This is an example CGI version of Zipdy
			written in php.
        Project:        Zipdy: Zip code distance calculator
        Home:           http://www.cryptnet.net/fsp/zipdy/
        Author:         V. Alex Brennen <vab@cryptnet.net>
                        http://www.cryptnet.net/people/vab/
*/


	if(!(ereg("([0-9]{5})", $ZIP1)))
	{
		echo "<H3>Error</H3>";
		echo "Zip code #1 does not appear to be a valid us zip code.\n";
		exit();
	}

	if(!(ereg("([0-9]{5})", $ZIP2)))
	{
		echo "<H3>Error</H3>";
		echo "Zip code #2 does not appear to be a valid us zip code.\n";
		exit();
	}

	$db = dbmopen("zips_gdbm","r");
	if($db == 0)
	{
		echo "Failed to open db file.\n";
		exit();
	}
	$result1 = dbmfetch($db, $ZIP1);

	if($result1 == "")
	{
		echo "Zip code #1 was not found in the database.\n";
		exit();
	}

	$result2 = dbmfetch($db,$ZIP2);
	if($result2 == "")
	{
		echo "Zip code #2 was not found in the database.\n";
		exit();
	}
	dbmclose($db);

	list($lon1,$lat1) = split(' ',$result1);
	list($lon2,$lat2) = split(' ',$result2);

	$the_distance = great_circle_distance($lat1,$lat2,$lon1,$lon2);
	echo "The distance between $ZIP1 and $ZIP2 is: $the_distance miles.\n";
	
	function great_circle_distance($lat1,$lat2,$lon1,$lon2)
	{
		/* Convert all the degrees to radians */
		$lat1 = deg_to_rad($lat1);
		$lon1 = deg_to_rad($lon1);
		$lat2 = deg_to_rad($lat2);
		$lon2 = deg_to_rad($lon2);

		/* Find the deltas */
		$delta_lat = $lat2 - $lat1;
		$delta_lon = $lon2 - $lon1;
	
		/* Find the Great Circle distance */
		$temp = pow(sin($delta_lat/2.0),2) + cos($lat1) * cos($lat2) * pow(sin($delta_lon/2.0),2);

		$EARTH_RADIUS = 3956;

		$distance = $EARTH_RADIUS * 2 * atan2(sqrt($temp),sqrt(1-$temp));

		return $distance;
	}

	function deg_to_rad($deg)
	{
		$radians = 0.0;
	
		$radians = $deg * M_PI/180.0;

		return($radians);
	}

?>
</BODY></HTML>
