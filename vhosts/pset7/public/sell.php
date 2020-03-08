<?php

    // Configuration
    require("../includes/config.php");
    
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        $rows = query("SELECT symbol, shares FROM stocks WHERE id = ?", $_SESSION["id"]);
        foreach ($rows as $row)
        {
            $stock = lookup($row["symbol"]);
            if($stock !== false)
            {
                $positions[] = [
                "name" => $stock["name"],
                "symbol" => $row["symbol"],
                "shares" => $row["shares"],
                ];
            }
        }
        
        render("sell_form.php", ["title" => "Sell Shares", "positions" => $positions]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $totalShares = query("SELECT shares FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $totalShares = $totalShares[0]["shares"];
        $stock = lookup($_POST["symbol"]);
        if (empty($_POST["symbol"]))
        {
            apologize("You must select a stock to sell");
            redirect("sell.php");
        }
        else if (empty($_POST["shares"]))
        {
            apologize("You must enter a value for 'No. of shares to sell'");
            redirect("sell.php");
        }
        else if ($_POST["shares"] < 0 || $_POST["shares"] > $totalShares)
        {
            apologize("The value you enter for \"No. of Shares\" must be a number between 0 and your total number of shares.", $totalShares);
            redirect("sell.php");
        }
        else if ($_POST["shares"] < $totalShares)
        {
            query("UPDATE stocks SET shares = shares - ? WHERE id = ? AND symbol = ?", $_POST["shares"], $_SESSION["id"], $_POST["symbol"]);
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["shares"] * $stock["price"], $_SESSION["id"]);
        }
        else if ($_POST["shares"] === $totalShares)
        {
            query("DELETE FROM stocks WHERE id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
            query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["shares"] * $stock["price"], $_SESSION["id"]);
        }
        
        query("INSERT INTO history (id, symbol, shares, price) VALUES (?, ?, ?, ?)", $_SESSION["id"], $_POST["symbol"], -1 * $_POST["shares"], $stock["price"]);
        render("sell.php", ["title" => "sold shares", "shares" => $_POST["shares"], "profit" => $_POST["shares"] * $stock["price"], "symbol" => $_POST["symbol"]]);
    }
?>
