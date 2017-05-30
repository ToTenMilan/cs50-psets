<?php
    // configuration
    require("../includes/config.php");
    
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("account_form.php", ["title" => "My account"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // save hashed new_password
        $new_password = password_hash($_POST["new_password"], PASSWORD_DEFAULT);
        // check for any blank fields
        if (empty($_POST["old_password"]) || empty($_POST["new_password"]) || empty($_POST["new_password_conf"]))
        {
            apologize("Any field can't be blank");
        }
        // grab from db current password hash
        $current_hash = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        // verify the old password
        if (password_verify($_POST["old_password"], $current_hash[0]["hash"]))
        {
            // verify confirmation password against new password
            if (password_verify($_POST["new_password_conf"], $new_password))
            {
                // update database with new password
                CS50::query("UPDATE users SET hash = ? WHERE id = ?", $new_password, $_SESSION["id"]);
                render("account.php", ["title" => "Password changed"]);
            }
            else
            {
                apologize("New password and confirmation password do not match");
            }
        }
        else
        {
            apologize("Your password is wrong.");
        }
    }
?>