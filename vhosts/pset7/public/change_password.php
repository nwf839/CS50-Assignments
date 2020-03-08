<?php
    
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("change_password_form.php", ["title" => "Change Password"]);
    }
    
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $rows = query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $row = $rows[0];
        if (empty($_POST["password"]))
        {
            apologize("Please enter a value for 'password'");
            redirect("change_password.php");
        }
        else if (empty($_POST["new_password"]) || empty($_POST["confirmation"]))
        {
            apologize("Please enter and confirm your new password");
            redirect("change_password.php");
        }
        else if (crypt($_POST["password"], $row["hash"]) != $row["hash"])
        {
            apologize("The password you entered was incorrect.");
            redirect("change_password.php");
        }
        else if ($_POST["new_password"] != $_POST["confirmation"])
        {
            apologize("Confirmation did not match password");
            redirect("change_password.php");
        }
        
        query("UPDATE users SET hash = ? WHERE id = ?", crypt($_POST["new_password"]), $_SESSION["id"]);
        redirect("index.php");
    }
?>
