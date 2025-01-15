function isMarkerInsidePolygon(marker, poly) {
    var polyPoints = poly.getLatLngs()[0];
    var x = marker.getLatLng().lat, y = marker.getLatLng().lng;

    var inside = false;
    for (var i = 0, j = polyPoints.length - 1; i < polyPoints.length; j = i++) {
        var xi = polyPoints[i].lat, yi = polyPoints[i].lng;
        var xj = polyPoints[j].lat, yj = polyPoints[j].lng;

        var intersect = ((yi > y) !== (yj > y)) &&
            (x < ((xj - xi) * (y - yi)) / (yj - yi) + xi);
        if (intersect) inside = !inside;
    }

    return inside;
}

function meassurementSetup() {
    // Get amount of meassurements pr axis
    var mX = document.getElementById("meassureX").value;
    var mY = document.getElementById("meassureY").value;

    // Get polygon
    var poly;
    drawnItems.eachLayer(function(existingLayer) {
        if (existingLayer instanceof L.Polygon) {
            poly = existingLayer;
        }
    });
    if (poly == undefined) {
        alert("Vælg både baseposition og mark afgrænsning for at beregne målepositioner!")
        return
    }

    // Find polygon size
    var polyTopLeft = poly.getBounds().getNorthWest();
    var polyBottomRight = poly.getBounds().getSouthEast();

    var polyWidth = polyTopLeft.lng - polyBottomRight.lng;
    var polyHeight = polyTopLeft.lat - polyBottomRight.lat;

    var meassureDistX = polyWidth / mX;
    var meassureDistY = polyHeight / mY;

    // Remove markers
    meassureMarkersLayer.clearLayers();

    // Add the new markers
    var currentX = polyTopLeft.lng - meassureDistX / 2;
    var currentY = polyTopLeft.lat - meassureDistY / 2;
    var tempLatLng;
    var tempMarker;
    for (var ix = 0; ix < mX; ix++) {
        currentY = polyTopLeft.lat - meassureDistY / 2;
        for (var iy = 0; iy < mY; iy++) {
            tempLatLng = new L.LatLng(currentY, currentX);
            tempMarker = new L.marker(tempLatLng);
            if (isMarkerInsidePolygon(tempMarker, poly)) {
                tempMarker.addTo(meassureMarkersLayer);
            }

            // X i positiv retning
            // Y i negativ retning
            currentY -= meassureDistY;
        }
        currentX -= meassureDistX;
    }


}