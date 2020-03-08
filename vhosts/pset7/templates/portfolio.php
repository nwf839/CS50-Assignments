<?php foreach ($positions as $key => $position): ?>
    <div>
        <tr>
            <td><b>Company <?= $key + 1?>:</b></td>
            <br>
            <td><b>Name:</b> <?= $position["name"]?></td>
            <br>
            <td><b>Symbol:</b> <?= $position["symbol"]?></td>
            <br>
            <td><b>Shares:</b> <?= $position["shares"]?></td>
            <br>
            <td><b>Price:</b> <?= number_format($position["price"], 2)?></td>
            <br>
            <br>
            <br>
        </tr>
    </div>
<?php endforeach?>
<div>
    <b>Total Funds Available:</b> <?= $cash?>
</div>
