.pragma library

function formatMoney(amount) {
    return Number(amount).toLocaleString(Qt.locale(), "f", 0);
}

function formatMoneyShort(amount) {
    var shortString = "";
    var base = 1;

    var million = 1000000;
    var thousand = 1000;

    if (amount >= million) {
        base = million;
    } else if (amount >= thousand) {
        base = thousand;
    }

    if (base != 1)
    {
        var hasfractionDigits = (amount % base !== 0)
        if (hasfractionDigits) {
            amount = Math.floor(amount * 10 / base) / 10
        } else {
            amount = amount/base
        }

        shortString = Number(amount).toLocaleString(Qt.locale(), "f", hasfractionDigits ? 1 : 0);

        if (base == thousand) {
            shortString += "K";
        } else if (base == million) {
            shortString += "M";
        }
    }
    else
    {
        shortString = Number(amount).toLocaleString(Qt.locale(), "f", 0);
    }

    return shortString;
}

function getSecondsLeftToTime(endTimestamp) {
    var currentTimestamp = Math.floor((new Date().getTime()) / 1000);
    var secondsLeft = endTimestamp - currentTimestamp;

    return secondsLeft;
}

function getSecondsPassedFromTime(startTimestamp) {
    var currentTimestamp = Math.floor(new Date().getTime() / 1000);
    var secondsPassed = currentTimestamp - startTimestamp;

    return secondsPassed;
}

function formatSecondsToHMSString(seconds) {
    var date = new Date(seconds * 1000);

    var hours = numberToTwoDigitsString(Math.floor(seconds / 3600));
    var m = numberToTwoDigitsString(date.getUTCMinutes());
    var s = numberToTwoDigitsString(date.getUTCSeconds());

    if (hours === "00") {
        return m + ":" + s;
    }

    return hours + ":" + m + ":" + s;
}

function numberToTwoDigitsString(number) {
    return number < 10 ? ("0" + number) : number;
}
