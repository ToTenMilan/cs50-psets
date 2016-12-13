<h2>History</h2>
<table class="table">
    <div>
        <tr>
            <td class="cell_top">Transaction</td>
            <td class="cell_top">Date & time</td>
            <td class="cell_top">Symbol</td>
            <td class="cell_top">Shares</td>
            <td class="cell_top">Price</td>
        </tr>
        <?php foreach ($positions as $position): ?>
        
        <tr class="table">
            <td class="cell"><?= $position["transaction"] ?></td>
            <td class="cell"><?= $position["datetime"] ?></td>
            <td class="cell"><?= $position["symbol"] ?></td>
            <td class="cell"><?= $position["shares"] ?></td>
            <td class="cell">$<?= $position["price"] ?></td>
        </tr>
        
    
        <?php endforeach ?>
    </div>
</table>
