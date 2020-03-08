<?php

    // Configuration
    require("../includes/config.php");
    
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $cash = query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        $cash = $cash[0]["cash"];
        render("buy_form.php", ["title" => "Buy stocks", "cash" => $cash]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        $totalPrice = $stock["price"] * $_POST["shares"];
        $sharesOwned = query("SELECT shares FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        if (empty($_POST["symbol"]))
        {
            apologize("You must enter a symbol for the stock you would like to buy.");
            redirect("buy.php");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must enter a value for 'No. of shares to buy'");
            redirect("buy.php");
        }
        else if (preg_match("/^\d+$/", $_POST["shares"]) === false)
        {
            apologize("'No. of shares to buy' must be a non-negative integer");
            redirect("buy.php");
        }
        else if ($totalPrice > $_POST["cash"])
        {
            apologize("You don't have enough cash.");
            redirect("buy.php");
        }
        else if($stock === false)
        {
            apologize("The stock you are looking for doesn't exist.");
            redirect("buy.php");
        }
        else if ($totalPrice <= $_POST["cash"])
        {
            query("INSERT INTO stocks (id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"]);
            query("UPDATE users SET cash = cash - ? WHERE id = ?", $_POST["shares"] * $stock["price"], $_SESSION["id"]);
            query("INSERT INTO history (id, symbol, shares, price) VALUES(?, ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], $_POST["shares"], $stock["price"]);
            render("buy.php", ["title" => "Successful purchase", "cost" => $_POST["shares"] * $stock["price"], "symbol" => $_POST["symbol"], "shares" => $_POST["shares"]]);
        }
    }
?>
