<?php
/* homepage of cs50 finance */

    // configuration
    require("../includes/config.php");
    // save in $rows symbol and shares columns of current user
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    
            // print_r($rows);
            // print_r("</br></br>");        
            // print_r($rows[0]);
            // print_r("</br>");  
            // print_r($rows[1]);
            // print_r("</br>");  
            // print_r($rows[2]);
            // print_r("</br></br>"); 
                    
    $positions = [];
    // $sum_total = 0;
    $balance = 0;
    
            // print_r("positions array: ");
            // print_r($positions);
            // print_r("</br></br>");
            
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
        
                // print_r("stock array: ");
                // print_r($stock);
                // print_r("</br>");
                // print_r("</br></br>");
                
        if ($stock !== false)
        {
            $total = $row["shares"] * $stock["price"];
            
            $positions[] = [
                "name" => $stock["name"],
                "price" => $stock["price"],
                "shares" => $row["shares"],
                "symbol" => $row["symbol"],
                "total" => $total
            ];
            
                // print_r($stock["name"]);
                // print_r("</br>");
                // print_r($stock["price"]);
                // print_r("</br>");
                // print_r($row["shares"]);
                // print_r("</br>");
                // print_r($row["symbol"]);
                // print_r("</br></br>");
                // print_r($total);
                // print_r("</br></br>");
                
            $balance = $balance + $total;
            
                // print_r("this is total sum: ");
                // print_r($sum_total);
                // print_r("</br></br>");
        }
    }
    // grab from db current user's cash value  
    $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
        // print_r($cash);
        // print_r("</br></br>");
        
    // update total sum (free cash + value of all stocks)
    $balance = $balance + $cash[0]["cash"];
    
        // print_r($sum_total);
        // print_r("</br></br>");
        
    $cash[0]["cash"] = number_format($cash[0]["cash"], $decimals = 2);
    // $balance = ["balance" => $sum_total];
    $balance = number_format($balance, $decimals = 2);
    
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "balance" => $balance, "cash" => $cash, "title" => "Portfolio"]);

?>

