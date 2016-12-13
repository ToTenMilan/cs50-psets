<?php

// configuration
    require("../includes/config.php");
    // get from database current user's transaction rows
    $rows = CS50::query("SELECT transaction, datetime, symbol, shares, price FROM history WHERE user_id = ?", $_SESSION["id"]);
    // create empty array for use after foreach loop
    $positions = [];
    // put values to positions array
    foreach ($rows as $row)
    {
        $positions[] = [
            "transaction" => $row["transaction"],
            "datetime" => $row["datetime"],
            "symbol" => $row["symbol"],
            "shares" => $row["shares"],
            "price" => $row["price"],
        ];
    }
    send array to view
    render("history.php", ["positions" => $positions, "title" => "History"]);
?>
