<?php

// configuration
    require("../includes/config.php");
    // save in $rows symbol and shares columns of current user
    $rows = CS50::query("SELECT transaction, datetime, symbol, shares, price FROM history WHERE user_id = ?", $_SESSION["id"]);
    $positions = [];
    foreach ($rows as $row)
    {
        $positions[] = [
            "transaction" => $row["transaction"],
            "datetime" => $row["datetime"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => number_format($row["price"], 2)
        ];
    }
    render("history.php", ["positions" => $positions, "title" => "History"]);

?>