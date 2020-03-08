<?php
    
    require("../includes/config.php");
    
    $rows = query("SELECT symbol, shares, price, time FROM history WHERE id = ?", $_SESSION["id"]);
    
    $positions = [];
    foreach ($rows as $row)
    {
        $positions[] = [
        "symbol" => $row["symbol"],
        "shares" => $row["shares"],
        "price" => $row["price"],
        "time" => $row["time"]
        ];
    }

    render("history.php", ["title" => "history", "positions" => $positions]);
?>
