<?php
    require("../includes/config.php");
                                
    // displays an HTML form via which a user can submit a stock’s symbol
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        render("quote_form.php", ["title" => "Choose stock symbol"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // grab input from user and capitalize it
        $input_stock_symbol = strtoupper($_POST["symbol"]);
        if (empty($input_stock_symbol))
        {
            apologize("Please choose a valid symbol");
        }
        // check iwhether symbol exists in yahoo            
        $yahoo_stock_array = lookup($input_stock_symbol);
        // format price to two places after comma
        $yahoo_price = number_format($yahoo_stock_array["price"], $decimals = 2);
        // displays a stock’s current price if user input is in yahoo db
        if ($yahoo_stock_array["symbol"] == $input_stock_symbol)
        {
            render("quote.php", ["price" => $yahoo_price, "name" => $yahoo_stock_array["name"], "title" => "Stock price"]);
        }
        else
        {
            apologize("There is no such symbol.");
        }
    }
?>
