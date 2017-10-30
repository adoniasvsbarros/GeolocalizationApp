// Globals
var map;
var kml = {
 a: { name: "Layer 1", url:"https://sites.google.com/site/gpsphotoapp/files/kmzphotos.kmz?attredirects=0&d=1" },
 b: { name: "Layer 2", url:"https://sites.google.com/site/gpsphotoapp/files/example.kmz?attredirects=0&d=1" }
};

function loadMap() {
  var g = google.maps;
  var opts_map = {
                  center: new g.LatLng(52.052491, 9.84375),
                  zoom: 5,
                  mapTypeIds: g.MapTypeId.ROADMAP
  };
  map = new g.Map(document.getElementById("map"), opts_map);
  createSidebar();
}


function addRow() {
    var div = document.createElement('div');

    div.className = 'row';

    div.innerHTML = '<input type="text" name="name" value="" />\
        <input type="text" name="value" value="" />\
        <label> <input type="checkbox" name="check" value="1" /> Checked? </label>\
        <input type="button" value="-" onclick="removeRow(this)">';

     document.getElementById('content').appendChild(div);
}


function toggleKML(checked, id) {
  if (checked) {
    var layer = new google.maps.KmlLayer(kml[id].url);

   // This is the new created object not the url property of kml
  kml[id].obj = layer;
  kml[id].obj.setMap(map);

  // Trying the store the viewport of every displayed layer
//  google.maps.event.addListenerOnce(layer, "defaultviewport_changed", function() {
  google.maps.event.addListenerOnce(layer, "metadata_changed", function() {

    // Best results using this listener and getDefaultViewport
    kml[id].bounds = this.getDefaultViewport();
  });
 }
 else {
  kml[id].obj.setMap(null);
  delete kml[id].obj;
 }
}



function zoomToOverlay(nr, id) {

 var box = document.forms["myform"].elements["box"][nr];
 if (box.checked) {
   map.fitBounds(kml[id].bounds);
 }
 else {
   box.click();
 }
}


function removeAll() {

 for (var prop in kml) {
  if (kml[prop].obj) {
   kml[prop].obj.setMap(null);
   delete kml[prop].obj;
  }
 }
 var boxes = document.getElementsByName("box");
 for (var i = 0, m; m = boxes[i]; i++) {
  m.checked = false;
 }
}


function createSidebar() {

 var i = -1;
 var html = "<form name='myform' id='myform'>";
 for (var prop in kml) {
  i++;
  html += "<p><input name='box' type='checkbox' id='" + prop + "'" +
  " onclick='toggleKML(this.checked, this.id)' \/>" +
  "&nbsp;<a href='#' onclick=\"zoomToOverlay(" + i + ", '" +
  prop + "');return false;\">" +
  kml[prop].name + "<\/a><\/p>";
 }
  html += "<p><a href='#' onclick='removeAll();return false;'>" +
  "Clear All<\/a><\/p><\/form>";

  html += "<p><a href='#' onclick='loadMap();return false;'>" +
  "Reset Position<\/a><\/p><\/form>";

 document.getElementById("sidebar").innerHTML = html;
}

window.onload = loadMap;

