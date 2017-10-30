<p>GeolocalizationApp - Creating .kmz files(markplace) capable of locate images in maps </p>
<h3> TO USERS:</h3>

<h2>What is the objective?</h2>
<p>Locate any photo you took in the world and locate where you took them. Basically, you have a program capable of receiving any directory containing pictures taken by any device or camera and if these photos have information about their location we will find it for you and create a .kmz file with the location of this photos. The .kmz file is widely supported in maps. You can add this file to any map and then see the location of your photos.</p>
<h2>How to get the program to work？</h2>

<h2>System requirements</h2>
<p>EXIF tool</p>
<p>ImageMagick</p>
<p>Libexif library</p>
<ol>
<li>In order to install the library get into the libexif-0.6.21 directory and click install.</li>
<li>A .txt file will be opened with all the instructions of installation</li>
<li>Briefly, type these shell commands to configure `./configure; make; make install', build, and install this package.</li>
</ol>

<h2>Instructions</h2>
<ol><li>After downloading the GeolocalizationApp open a terminal (ctrl+alt+t)</li>
   <li>Access the main directory of the app</li>
   <li>Type in the terminal the command: "gcc main.c functions.h -o main -lexif" to compile the program</li>
   <li>In order to execute the program you must be inside the main directory and type ./main <name_of_directory> renaming <name_of_directory> for the absolut path of the directory of your photos and them execute</li>
   <li>An info.kmz file will be generated inside the main directory of the program, inside this file there is a folder with the compressed images and a .kml file with the information about your photos. A folder kmzphotos with a .kml and a folder with compressed photos will be also generated.</li>
   <li>With the file kmzphotos.kmz file you will be able to go to any maps that support the .kmz and insert this file in order to see the location of the photos you took</li>
   <li>A photos file (photos) is given as example inside the main directory</li>
</ol>

<h2>How to show your kmz in a layer inside the application HTML</h2>
<ol>
  <li>After generating the KMZ file you must put it in a web server in order to get a public URL with this file</li>
  <li>Go to app_html/maps.js and inside the file go to var kml = { ...　}</li>
  <li>Add inside the var kml ,{"X" : { name: "Layer N", url:" your URL " }, <br>for example: if inside the var kml you have: <br>var kml = {
 <br>a: { name: "Layer 1", url:"https://sites.google.com/site/gpsphotoapp/files/kmzphotos.kmz?attredirects=0&d=1" }
}<br>, "X" should be b and "N" should be 2, <br>so var kml = {
 <br>a: { name: "Layer 1", url:"https://sites.google.com/site/gpsphotoapp/files/kmzphotos.kmz?attredirects=0&d=1" },
 <br>b: { name: "Layer 2", url:"https://sites.google.com/site/gpsphotoapp/files/example.kmz?attredirects=0&d=1" }
}; 
</li>
  <li>A new layer called "Layer N" will be displayed in the html and you will be able to see it if you check the box</li>
</ol>

<h2>How to open the application HTML</h2>
<ol>
  <li>Go to app_html/index.html</li>
</ol>


<h2>How to show this documentation</h2>
<ol>
  <li>Go to html/index.html</li>
</ol>

<h2>How to add images in the gallery</h2>
<ol>
  <li>Go to html/photos.html</li>
  <li>Add your image in the file photos</li>
  <li>Inside the div id="insidecarousel"  add a new div with the following informations<br> div class="item active"<br><img src="photos/"yourPhotoName".jpg" alt=" "N"Slide"> where "yourPhotoName" and "N" are your photo name and a different name to your slide</div>
  </li>
</ol>

<h2>List of possible ERROR messages:</h2>
<ol>
<li>ERROR 1: File  has no latitude tag</li>
<li>ERROR 2: File has no longitude tag</li>
<li>ERROR 3: struct images[%d] not initialized</li>
<li>ERROR 4: Cannot open Input directory</li>
<li>EXIT: No file was provided</li>
</ol>

<h2>Important Links:</h2>
<ol>	
<li>[KMLDocumentation](https://developers.google.com/kml/documentation/)</li>
<li>[geoportal](https://www.geoportail.gouv.fr/carte)</li>
<li>[doxygem](http://www.stack.nl/~dimitri/doxygen/manual/index.html)</li>
<li>[libexif](http://libexif.sourceforge.net/api/)</li>
<li>[OpenStreetMap](https://www.openstreetmap.org/)</li>
<li>[EXIFtool](http://www.sno.phy.queensu.ca/~phil/exiftool/)</li>
<li>[ImageMagick](https://www.imagemagick.org/script/index.php)</li>

</ol>
