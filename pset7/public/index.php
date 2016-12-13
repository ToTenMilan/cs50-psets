<?php
/* homepage of cs50 finance */
    // configuration
    require("../includes/config.php");
    // save in $rows symbol and shares columns of current user
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $positions = [];
    // $sum_total = 0;
    $balance = 0;
    foreach ($rows as $row)
    {
        $stock = lookup($row["symbol"]);
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
            $balance = $balance + $total;
        }
    }
    // grab from db current user's cash value  
    $cash = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    // update total sum (free cash + value of all stocks)
    $balance = $balance + $cash[0]["cash"];
    $cash[0]["cash"] = number_format($cash[0]["cash"], $decimals = 2);
    // $balance = ["balance" => $sum_total];
    $balance = number_format($balance, $decimals = 2);
    // render portfolio
    render("portfolio.php", ["positions" => $positions, "balance" => $balance, "cash" => $cash, "title" => "Portfolio"]);
?>
