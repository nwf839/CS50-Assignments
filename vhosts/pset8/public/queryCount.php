<?php

    // Config
    require(__DIR__ . "/../includes/config.php");
    
    if (!isset ($_POST["eventObject"]))
    {
        http_response_code(400);
        exit;
    }
    
    else
    {
        $query = $_POST["eventObject"];
        var_dump($query);
    }

?>
