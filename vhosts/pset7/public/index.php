<?php

    // configuration
    require("../includes/config.php");
    
    // query stocks by user id
    $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    $cash = number_format($cash[0]["cash"], 2);
    $rows = query("SELECT symbol, shares FROM stocks WHERE id = ?", $_SESSION["id"]);
    $positions = [];
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        if ($stock !== false)
        {
            $positions[] = [
            "name" => $stock["name"],
            "price" => $stock["price"],
            "shares" => $row["shares"],
            "symbol" => $row["symbol"]
            ];
        }
    }


    // render portfolio
    render("portfolio.php", ["positions" => $positions, "cash" => $cash, "title" => "Portfolio"]);

?>
