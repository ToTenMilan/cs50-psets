<?php

    require("../includes/config.php");

    // -----------------
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("sell_form.php", ["title" => "Sell stock"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = strtoupper($_POST["symbol"]);
        $owned_shares = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
        if (empty($_POST["symbol"]))
        {
            apologize("Please choose a valid symbol");
        }
        if (!in_array($stock, $owned_shares[0]))
        {
            apologize("There is no sych stock in your portfolio");
        }
        
//             print_r("POST array: ");
//             print_r($_POST);
//             print_r("</br></br>");
//             print_r("\$stock variable: ");
//             print_r($stock);
//             print_r("</br></br>");  
            // print_r($rows[2]);
            // print_r("</br></br>"); 
        $s = lookup($stock);
        $stock_name = $s["name"];
//             print_r("\$s array: ");
//             print_r($s);
//             print_r("</br></br>"); 
                    // print_r("<p>\$s val: |".$s["symbol"]."|</p>");
        $shares_num = CS50::query("SELECT shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
//             print_r("\$shares_num array: ");
//             print_r($shares_num);
//             print_r("</br>");
//             print_r('$shares_num[0]["shares"] value is:');
//             print_r($shares_num[0]["shares"]);
//             print_r("</br></br>");
        $cash_to_update = $shares_num[0]["shares"] * $s["price"];
//             print_r("\$cash_to_update variable: ");
//             print_r($cash_to_update);
//             print_r("</br></br>");
//             print_r('$s["price"] array is: ');
//             print_r($s["price"]);
//             print_r("</br></br>"); 
 
        CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?",$cash_to_update , $_SESSION["id"]);
        
        render("sell.php", ["cash_to_update" => $cash_to_update, "name" => $stock_name, "title" => "Stocks sold"]);
        // displays, minimally, a stock’s latest price (if passed, via render, an appropriate value).
        // if ($s["symbol"] == strtoupper($_POST["symbol"]))
        // {
        //     render("quote.php", ["price" => $s["price"], "name" => $s["name"], "title" => "Stock price"]);
        //     // render("quote.php", ["price" => $s["price"], "name" => $s["name"], "title" => "Stock price"]);
        // }
        // else
        // {
        //     apologize("There is no such symbol.");
        // }
    }
?>
