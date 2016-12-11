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
        if (empty($_POST["symbol"]))
        {
            apologize("Please choose a valid symbol");
        }
            print_r("\$_POST[\"shares\"]: ");
            print_r($_POST["shares"]);
            print_r("</br>");
        if (empty($_POST["shares"]) || (!preg_match("/^\d+$/", $_POST["shares"])))
        {
            apologize("Please choose number of stocks to buy");
        }
        $stock = strtoupper($_POST["symbol"]);
            // print_r("POST array: ");
            // print_r($_POST);
            // print_r("</br>");
            // print_r("\$stock variable: ");
            // print_r($stock);
            // print_r("</br></br>");  
        $s = lookup($stock);
        // grab from db current user's cash value  
        $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        print_r("\$cash: ");
            print_r($cash);
            print_r("</br>");
        // calculate value of bought stocks to compare to cash
        $stocks_total_value = $s["price"] * $_POST["shares"];
        print_r("\$stocks_total_value variable is: ");
            print_r($stocks_total_value);
            print_r("</br></br>");
        
        // compare whether user has less cash then value of stocks requested to buy
        if ($cash[0]["cash"] < $stocks_total_value)
        {
            apologize("You dont have enough free cash to perform this operation");
        }
        if ($s)
        {
            CS50::query("INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $stock, $_POST["shares"]);
            // print_r("\$bought stocks array: ");
            // print_r($bought_stocks);
            // print_r("</br></br>");
            
            print_r("\$stock: ");
            print_r($stock);
            print_r("</br></br>");
            
            // save stock full name in $stock_name
            $stock_name = $s["name"];
            // print_r("\$s array: ");
            // print_r($s);
            // print_r("</br></br>"); 
                    // print_r("<p>\$s val: |".$s["symbol"]."|</p>");
            $total_price = $_POST["shares"] * $s["price"];
            print_r("\$total_price: ");
            print_r($total_price);
            print_r("</br></br>");
                    
            // $cash_to_update = $shares_num[0]["shares"] * $s["price"];
            //     print_r("\$cash_to_update variable: ");
            //     print_r($cash_to_update);
            //     print_r("</br></br>");
                    // remove free cash which user lose after buy
            CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $total_price , $_SESSION["id"]);
        
            
                // grab from db number of shares
            // $shares_num = CS50::query("SELECT shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
            //     print_r("\$shares_num array: ");
            //     print_r($shares_num);
            //     print_r("</br>");
            //     print_r('$shares_num[0]["shares"] value is:');
            //     print_r($shares_num[0]["shares"]);
            //     print_r("</br></br>");
                
                
            
                // print_r('$s["price"] array is: ');
                // print_r($s["price"]);
                // print_r("</br></br>"); 
     
            
            // CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?",$cash_to_update , $_SESSION["id"]);
            
            render("buy.php", ["total_price" => $total_price, "name" => $stock_name, "title" => "Stocks sold"]);
        }
        else
        {
            apologize("Please choose a valid symbol");
        }
    }
?>
