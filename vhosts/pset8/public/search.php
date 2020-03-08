<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // Search database for places matching $_GET["geo"]
    $geo = urlencode($_GET["geo"]);
    
    // Remove non-alphanumeric characters and country codes
    $query = preg_replace("/(%2C)/", " ", $geo);
    $query = preg_replace("/[^A-Za-z0-9 ]/", " ", $query);
    $query = preg_replace("/(\s[Uu][Ss][Aa]?)/", "", $query);
    
    
    // Explode query into array to separate region codes from place names
    $queryTerms = explode(" ", $query);
    
    $stateCodes = [];
    $booleanTerms = [];
    foreach ($queryTerms as $key => $term)
    {
        if (strlen($term) == 2)
        {
            $stateCodes[$key] = $term;
        }
        else if (strlen($term) > 3)
        {
            // Format terms for boolean text search
            $booleanTerms[$key] = "+" . $term . "*";
        }
    }
    
    // Implode arrays back into strings for querying
    $stateCodes = implode(" ", $stateCodes);
    $booleanTerms = implode(" ", $booleanTerms);
    
    if ($stateCodes === "")
    {
        $places = query("SELECT * FROM places WHERE MATCH(postal_code, place_name, admin_name1, admin_name2) AGAINST(? IN BOOLEAN MODE)", $booleanTerms);
    }
    else
    {
        $places = query("SELECT * FROM places WHERE admin_code1 = ? and MATCH(postal_code, place_name, admin_name1, admin_name2) AGAINST(? IN BOOLEAN MODE)", $stateCodes, $booleanTerms);
    }
       
    
    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));
?>
