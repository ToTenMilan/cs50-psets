<h2>Portfolio</h2>
<table class="table">
    
    <tr>
        <td class="cell_top">Name</td>
        <td class="cell_top">Symbol</td>
        <td class="cell_top">Shares</td>
        <td class="cell_top">Price</td>
        <td class="cell_top">Total</td>
    </tr>
    <?php foreach ($positions as $position): ?>
    
    <tr class="table">
        <td class="cell"><?= $position["name"] ?></td>
        <td class="cell"><?= $position["symbol"] ?></td>
        <td class="cell"><?= $position["shares"] ?></td>
        <td class="cell">$<?= $position["price"] ?></td>
        <td class="cell">$<?= $position["total"] ?></td>
    </tr>

    <?php endforeach ?>
    
</table>
<p class="bal">Free cash</p>
<p class="bal_sum">$<?= $cash[0]["cash"] ?></p>

<p class="bal">Current balance</p>
<p class="bal_sum">$<?= $balance ?></p>


