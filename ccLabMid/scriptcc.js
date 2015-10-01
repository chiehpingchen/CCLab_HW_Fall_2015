var map = null;
var infowindow;
var image = 'beermarkerv3.png';

var directionsDisplay;
var directionsService;
var newyork = {lat: 40.7369955, lng: -73.9922214};

function initMap() {
  // var newyork = {lat: 40.7369955, lng: -73.9922214};
  // var brklyn = {lat: 40.700359, lng: -73.922725};

  directionsDisplay = new google.maps.DirectionsRenderer();
  directionsService = new google.maps.DirectionsService();

  var myOptions = {
  center: new google.maps.LatLng(40.7369955, -73.9922214),
  mapTypeId: google.maps.MapTypeId.ROADMAP
};


  map = new google.maps.Map(document.getElementById('map'), {


                                                            // mapStyleCode ---------------------------------------
                                                              styles: [ {   "featureType": "administrative",
                                                                "elementType": "labels.text.fill",
                                                                "stylers": [
                                                                    {
                                                                        "color": "#444444"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "landscape",
                                                                "elementType": "all",
                                                                "stylers": [
                                                                    {
                                                                        "color": "#f4f4f4"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "poi",
                                                                "elementType": "all",
                                                                "stylers": [
                                                                    {
                                                                        "visibility": "off"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road",
                                                                "elementType": "all",
                                                                "stylers": [
                                                                    {
                                                                        "saturation": -100
                                                                    },
                                                                    {
                                                                        "lightness": 45
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road.highway",
                                                                "elementType": "all",
                                                                "stylers": [
                                                                    {
                                                                        "visibility": "simplified"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road.highway",
                                                                "elementType": "geometry",
                                                                "stylers": [
                                                                    {
                                                                        "visibility": "simplified"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road.highway",
                                                                "elementType": "geometry.fill",
                                                                "stylers": [
                                                                    {
                                                                        "color": "#ffce3d"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road.arterial",
                                                                "elementType": "geometry.stroke",
                                                                "stylers": [
                                                                    {
                                                                        "color": "#ffce3d"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road.arterial",
                                                                "elementType": "labels.icon",
                                                                "stylers": [
                                                                    {
                                                                        "visibility": "off"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "road.local",
                                                                "elementType": "geometry.stroke",
                                                                "stylers": [
                                                                    {
                                                                        "visibility": "on"
                                                                    },
                                                                    {
                                                                        "color": "#ffce3d"
                                                                    },
                                                                    {
                                                                        "weight": "0.52"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "transit",
                                                                "elementType": "all",
                                                                "stylers": [
                                                                    {
                                                                        "visibility": "off"
                                                                    }
                                                                ]
                                                            },
                                                            {
                                                                "featureType": "water",
                                                                "elementType": "all",
                                                                "stylers": [
                                                                    {
                                                                        "color": "#f6e5b4"
                                                                    },
                                                                    {
                                                                        "visibility": "on"
                                                                    }   ] }],
                                                            // mapStyleCode ---------------------------------------


    panControl: true,
    zoomControl: true,
    mapTypeControl: true,
    scaleControl: true,
    streetViewControl: true,
    overviewMapControl: true,

    center: newyork,
    zoom: 17,


  });



directionsDisplay.setMap(map);
directionsDisplay.setPanel(document.getElementById("direction-panel"));

var control = document.getElementById("control");
control.style.display = "block";





  infowindow = new google.maps.InfoWindow();

  var service = new google.maps.places.PlacesService(map);
  service.nearbySearch({
    location: newyork,
    radius: 500,
    types: ['bar']

  }, callback);
}





function callback(results, status) {
  if (status === google.maps.places.PlacesServiceStatus.OK) {
    for (var i = 0; i < results.length; i++) {
      createMarker(results[i]);
    }
  }
}

function calcRoute() {
  var start = document.getElementById('start').value;
  var end = document.getElementById('end').value;
  var request = {
    origin: start,
    destination: end,
    travelMode: google.maps.DirectionsTravelMode.TRANSIT
  };
  directionsService.route(request, function(response, status) {
    if (status == google.maps.DirectionsStatus.OK) {
      directionsDisplay.setDirections(response);
    }
  });
}

function createMarker(place) {
  var placeLoc = place.geometry.location;
  var marker = new google.maps.Marker({
      map: map,
      position: place.geometry.location,
      icon: image,
  });

      google.maps.event.addListener(marker, 'click',

        function() {
        var storename = place.name + "</br>" + "rating: " + place.rating + "</br>" + place.vicinity;
        var addresss = place.vicinity;
        var d12 = newyork.lat + "," + newyork.lng;
 
        infowindow.setContent(storename);
        $('#start').attr('value',d12);
        $('#bar-name').attr('value', place.name);
        $('#end').attr('value', addresss);

      infowindow.open(map, this);
  });


}