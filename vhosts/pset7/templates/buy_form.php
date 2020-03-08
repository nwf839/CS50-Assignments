<form action="buy.php" method="post">
    <fieldset>
        <div>
            <input autofocus class="form-control" name="symbol" placeholder="Ticker Symbol" type="text">
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="No. of shares to buy" type="number">
        </div>
        <div>
            <input type="hidden" name="cash" value="<?= $cash?>">
        </div>
        <div>
            <button type="submit" class="btn btn-default">Buy</button>
        </div>
    </fieldset>
</form>
