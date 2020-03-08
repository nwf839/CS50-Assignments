<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Get Quote"]);
    }
    
    // else if reached page via POST
    else if ($_SERVER["REQUEST_METHOD"] = "POST")
    {
        $stock = lookup($_POST["symbol"]);
        if ($stock === false)
        {
            apologize("The ticker symbol you entered was invalid");
            redirect("quote.php");
        }
        else
        {
            $stockName = $stock["name"];
            $stockPrice = number_format($stock["price"], 2);
            render("quote.php", ["title" => "Quote Information", "stockName" => $stockName, "stockPrice" => $stockPrice]);
        }
    }

?>
