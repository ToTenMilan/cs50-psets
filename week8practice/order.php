<!DOCTYPE html>
<html>
<head lang="en-US">
    <title>multiplication results</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
<?php 

    $num = $_GET["number"];
    echo "<table border=\"1\">";
    for($i = 0; $i < $num; $i++)
    {
        echo'<tr>';
        for($j = 0; $j < $num; $j++)
        {
            echo'<td>'.($i+1)*($j+1).'</td>';
            
            // echo("<tr><td>$num</td></tr>");
        }
        echo'</tr>';
    }
    echo"</table>";

?>
</body>
</html>