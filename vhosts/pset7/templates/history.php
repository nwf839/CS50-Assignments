<?php foreach ($positions as $position): ?>
    <div>
        <tr>
            <td><b>Transaction at <?=$position["time"]?>:</b></td>
            <br>
            <td>Change in shares: <?=$position["shares"]?></td>
            <br>
            <td>Price at time of purchase/sale:</b> <?=$position["price"]?></td>
            <br>
            <br>
        </tr>
    </div>
<?php endforeach ?>
