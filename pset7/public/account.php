<?php

    // configuration
    require("../includes/config.php");
    
    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("account_form.php", ["title" => "My account"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // $old_password = password_hash($_POST["old_password"], PASSWORD_BCRYPT);
                    print_r("old password: "); print_r($_POST["old_password"]); print_r("</br></br>");
        $new_password = password_hash($_POST["new_password"], PASSWORD_DEFAULT);
                    print_r("new password: "); print_r($_POST["new_password"]); print_r("</br></br>");
        // $new_password_conf = password_hash($_POST["new_password_conf"], PASSWORD_BCRYPT);
                    print_r("new password conf: "); print_r($_POST["new_password_conf"]); print_r("</br></br>");
        if (empty($_POST["old_password"]) || empty($_POST["new_password"]) || empty($_POST["new_password_conf"]))
        {
            apologize("Any field can't be blank");
        }
        
        $current_hash = CS50::query("SELECT hash FROM users WHERE id = ?", $_SESSION["id"]);
        $current_hash = $current_hash[0]["hash"];
                    print_r("current hash: "); print_r($current_hash); print_r("</br></br>");
        $verified = password_verify($_POST["old_password"], $current_hash);
                    print_r("verified: "); print_r($verified); print_r("</br></br>");
        if ($verified)
        {
            if (password_verify($_POST["new_password_conf"], $new_password))
            {
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
