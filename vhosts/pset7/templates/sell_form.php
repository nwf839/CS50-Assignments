<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select name="symbol" class="form-control">
            <?php foreach ($positions as $position): ?>
                <option value= "<?= $position['symbol'] ?>"><?= $position['name'] ?> (<?= $position['symbol'] ?>)</option>
            <?php endforeach ?>
            </select>
            <input class="form-control" name="shares" placeholder="No. of Shares" type="number" min="0" >
        </div>
        <div>
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
