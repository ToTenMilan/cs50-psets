<?php
    
    require("../includes/config.php");
    
    // dump($_POST["symbol"]);
    // dump($_POST["name"]);
    // dump($_POST["price"]);
                                // $a =1;
                                // $b =2;
                                
        // displays an HTML form via which a user can submit a stock’s symbol
        
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("quote_form.php", ["title" => "Choose stock symbol"]);
    }
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if (empty($_POST["symbol"]))
        {
            apologize("Please choose a valid symbol");
        }
        $stock = strtoupper($_POST["symbol"]);
                    print_r("<p>\$stock var: |$stock|</p>");
                    print_r("<p>POST val: |".$_POST["symbol"]."|</p>");
        $s = lookup($stock);
                    print_r("<p>\$s val: |".$s["symbol"]."|</p>");
        $s["price"] = number_format($s["price"], $decimals = 2);
        
        // displays, minimally, a stock’s latest price (if passed, via render, an appropriate value).
        if ($s["symbol"] == strtoupper($_POST["symbol"]))
        {
            render("quote.php", ["price" => $s["price"], "name" => $s["name"], "title" => "Stock price"]);
            // render("quote.php", ["price" => $s["price"], "name" => $s["name"], "title" => "Stock price"]);
        }
        else
        {
            apologize("There is no such symbol.");
        }
    }
?>