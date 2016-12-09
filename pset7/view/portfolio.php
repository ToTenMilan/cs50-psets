<table>
    <div>
        <?php foreach ($positions as $position): ?>
    
        <tr class="table table-striped">
            <td><?= $position["name"] ?></td>
            <td><?= $position["symbol"] ?></td>
            <td><?= $position["shares"] ?></td>
            <td><?= $position["price"] ?></td>
        </tr>
    
        <?php endforeach ?>
    </div>
</table>
