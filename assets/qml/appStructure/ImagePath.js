.pragma library

// Enum-like
var PerSize = "perSize/"
var OneSize = "oneSize/"
var AnySize = "anySize/"

function resolve(relativePath, imageName) {
    if (imageName.length === 0) {
        return ""
    }

    return relativePath + "images/" + imageName
}
