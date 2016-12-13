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
        // save input in variable $input_symbol
        $input_symbol = strtoupper($_POST["symbol"]);
        // lookup $input_symbol for variable and save it in $yahoo_stock array
        $yahoo_stock = lookup($input_symbol);
        // save symbol of $yahoo_stock array in $yahoo_symbol
        $yahoo_symbol = $yahoo_stock["symbol"];
        
        if (empty($input_symbol))
        {
            apologize("Please choose a valid symbol");
        }
        if ($input_symbol !== $yahoo_symbol)
        {
            apologize("There is no such symbol");
        }
        else
        {
            // search the database for a symbol given in input
            $db_symbol = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $input_symbol);
            if ($input_symbol === $db_symbol[0]["symbol"])
            {
                // get from datebase number of shares of $db_symbol
                $shares_owned = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $input_symbol);
                // calculate the total amount
                $yahoo_price = $yahoo_stock["price"];
                $shares_owned_value = $shares_owned[0]["shares"];
                $total = $shares_owned_value * $yahoo_price;
                // delete row with requested symbol from portfolios table
                CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $input_symbol);
                // update database users with $total_sum + current cash amount
                CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total , $_SESSION["id"]);
                $yahoo_name = $yahoo_stock["name"];
                render("sell.php", ["total" => $total, "name" => $yahoo_name, "title" => "Stocks sold"]);
            }
            else
            {
                apologize("You dont have any stocks of this company");
            }
        }
    }
?>
