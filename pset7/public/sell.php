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
        $input_symbol = strtoupper($_POST["symbol"]);
        $yahoo_stock = lookup($input_symbol);
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
            $db_symbol = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $input_symbol);
                    // print_r("input symbol: "); print_r($input_symbol);
                    // print_r("db symbol: "); print_r($db_symbol);
            if ($input_symbol === $db_symbol[0]["symbol"])
            {
                            print_r("input symbol: "); print_r($input_symbol); print_r("</br></br>");
                $shares_owned = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $input_symbol);
                $yahoo_price = $yahoo_stock["price"];
                            print_r("yahoo price: "); print_r($yahoo_price); print_r("</br></br>");
                $shares_owned_value = $shares_owned[0]["shares"];
                            print_r("shares owned value: "); print_r($shares_owned_value); print_r("</br></br>");
                $total = $shares_owned_value * $yahoo_price;
                            print_r("total: "); print_r($total); print_r("</br></br>");
                CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $input_symbol);
                            print_r("after first db query"); print_r("</br></br>");
                CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $total , $_SESSION["id"]);
                            print_r("after second db query"); print_r("</br></br>");
                            
                $yahoo_name = $yahoo_stock["name"];
                            print_r("renders view</br>");
                render("sell.php", ["total" => $total, "name" => $yahoo_name, "title" => "Stocks sold"]);
            }
            else
            {
                apologize("You dont have any stocks of this company");
            }
        }
    }
?>

            <!--print_r("\$owned_shareS[0][\"symbol\"]: ");-->
            <!--print_r($owned_shares[0]["symbol"]);-->
            <!--print_r("</br></br>");  -->
