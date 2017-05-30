<?php
    require("../includes/config.php");
    // -----------------
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("buy_form.php", ["title" => "buy stock"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // create variables for readability
        $input_symbol = strtoupper($_POST["symbol"]);
        $input_shares = $_POST["shares"];
        $yahoo_stock = lookup($input_symbol);
        $yahoo_price = $yahoo_stock["price"];
        
        if (empty($input_symbol))
        {
            apologize("Input field may not be blank");
        }
        if (empty($input_shares) || (!preg_match("/^\d+$/", $input_shares)))
        {
            apologize("Please choose number of stocks to buy");
        }
        // grab from db current user's cash value  
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        // calculale total value of bought stocks
        $total_price = $input_shares * $yahoo_price;
        // compare whether user has less cash then value of stocks requested to buy
        if ($cash[0]["cash"] < $total_price)
        {
            apologize("You dont have enough free cash to perform this operation");
        }
        // buy stocks if all conditions mare met
        if ($yahoo_stock)
        {
            // update db with chosen symbol (stocks), if rows are duplicating, merge them
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $input_symbol, $input_shares);
            // update free cash
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $total_price , $_SESSION["id"]);
            // update 'history' table
            CS50::query("INSERT INTO `history`(`user_id`, `transaction`, `symbol`, `shares`, `price`) VALUES (?, ?, ?, ?, ?)", $_SESSION["id"], "BUY", $input_symbol, $input_shares, $yahoo_price);
            $stock_name = $yahoo_stock["name"];
            render("buy.php", ["total_price" => number_format($total_price, 2), "name" => $stock_name, "title" => "Stocks sold"]);
        }
        else
        {
            apologize("Please choose a valid symbol");
        }
    }
?>