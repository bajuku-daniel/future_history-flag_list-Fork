(function ($) {

  // Style the gmap markers blue and violet
  var fh_marker_blue = new google.maps.MarkerImage(
    '/sites/default/files/gmap-files/fh-poi-blue.png',
    new google.maps.Size(25, 25),
    new google.maps.Point(0, 0), //origin
    new google.maps.Point(12, 12) //anchor point
  );
  var fh_marker_violet = new google.maps.MarkerImage(
    '/sites/default/files/gmap-files/fh-poi-violet.png',
    new google.maps.Size(25, 25),
    new google.maps.Point(0, 0), //origin
    new google.maps.Point(12, 12) //anchor point
  );

  var tour_url = '/de/fh_view/list_tour_content';
  var pois_by_nid = [];
  var mapCenter;
  var allTourMarker = [];
  var info_content = [];
  var mapUpdate = 0;
  var directionsService = new google.maps.DirectionsService;
  var directionsDisplay = new google.maps.DirectionsRenderer;
  var infowindow = new google.maps.InfoWindow();
  var infoBox = new InfoBox();

  var maxTourDistance = 10000;








  function showTourOnMap() {
    var edit_tourdata = [];
    $('#entry-order tr').each(function() {
      if ($(this).attr('lat_value')) {
        edit_tourdata.push({
          lat: $(this).attr('lat_value'),
          lng: $(this).attr('lng_value'),
          nid: $(this).attr('id'),
          name: $(this).attr('name'),
          year: $(this).attr('year'),
          image: $(this).find('img').attr('src'),
        });
      }
    });

    directionsDisplay.setMap(Drupal.futurehistoryTourEditMap.map);
    directionsDisplay.setOptions({suppressMarkers: true});

    calculateAndDisplayRoute(directionsService, directionsDisplay, edit_tourdata);
  }

  function calculateAndDisplayRoute(directionsService, directionsDisplay, edit_tourdata) {
    var waypts = [];
    var tour_pois = [];
    var initTourDistance = $('input[name=tour_distance]').val();


    for (var i = 0; i < edit_tourdata.length; i++) {
      if (i === 0) {
        // Start EndPunkt benötigen Datenformat mit lng/lat oder Text e.g. New York,US
        my_origin = edit_tourdata[i]['lat'] + "," + edit_tourdata[i]['lng'];

        //create the array for our tour pois
        tour_pois.push({
          lat: edit_tourdata[i]['lat'],
          lng: edit_tourdata[i]['lng'],
          nid: edit_tourdata[i]['nid'],
          name: edit_tourdata[i]['name'],
          year: edit_tourdata[i]['year'],
          image: edit_tourdata[i]['image']

        });
        // overwrite with 0 in next step - than we have a tour - otherway we have a single poi :)
        var one_poi = 1;

      } else if (i === edit_tourdata.length - 1) {
        my_destination = edit_tourdata[i]['lat'] + "," + edit_tourdata[i]['lng'];
        tour_pois.push({
          lat: edit_tourdata[i]['lat'],
          lng: edit_tourdata[i]['lng'],
          nid: edit_tourdata[i]['nid'],
          name: edit_tourdata[i]['name'],
          year: edit_tourdata[i]['year'],
          image: edit_tourdata[i]['image']
        });
        one_poi = 0;
      } else {
        // waypoints benörigen datenformat mit folgender Struktur info
        waypts.push({
          location: new google.maps.LatLng(edit_tourdata[i]['lat'], edit_tourdata[i]['lng']),
          stopover: true
        });
        tour_pois.push({
          lat: edit_tourdata[i]['lat'],
          lng: edit_tourdata[i]['lng'],
          nid: edit_tourdata[i]['nid'],
          name: edit_tourdata[i]['name'],
          year: edit_tourdata[i]['year'],
          image: edit_tourdata[i]['image']
        });
      }
    }

    // check if we have more than one poi in our tour
    if (one_poi == 0) {
      if (initTourDistance < maxTourDistance) {
        directionsService.route({
          origin: my_origin,
          destination: my_destination,
          waypoints: waypts,
          optimizeWaypoints: false,
          travelMode: google.maps.TravelMode.WALKING
        }, function (response, status) {
          if (status === google.maps.DirectionsStatus.OK) {
            directionsDisplay.setDirections(response);
          } else {
            window.alert('Directions request failed due to ' + status);
          }
        });
      } else {
        if ( !$('#tour_warning').length ){
          $('#futurehistory-tour-edit-map').before( '<p id="tour_warning">Wegstrecke ist größer als 10km - es wird keine Route eingezeichnet</p>');
        }
      }
    } else {
      var poiPosition = new google.maps.LatLng(tour_pois[0]['lat'],tour_pois[0]['lng']);
      Drupal.futurehistoryTourEditMap.map.panTo(poiPosition);
    }

    for (var i = 0; i < tour_pois.length; i++) {
      var poiPosition = new google.maps.LatLng(tour_pois[i]['lat'],tour_pois[i]['lng']);
      var poiId = tour_pois[i]['nid'];
      var poi_year = tour_pois[i]['year'];
      var poi_name = tour_pois[i]['name'];
      var image = tour_pois[i]['image'];
      var title = poi_name + ' | ' + poi_year;
      Drupal.futurehistoryTourEditMap.marker = new google.maps.Marker({
        //title: title,
        id: poiId,
        position: poiPosition,
        map: Drupal.futurehistoryTourEditMap.map,
        icon: fh_marker_blue,
      });
      //add the marker hover listner
      google.maps.event.addListener(Drupal.futurehistoryTourEditMap.marker, 'mouseover', function () {
        hoverThumb('hover',this.id);
        hoverMarker('hover',this.id);
      });
      google.maps.event.addListener(Drupal.futurehistoryTourEditMap.marker, 'mouseout', function () {
        hoverThumb('out',this.id);
        hoverMarker('out',this.id)
      });

      //put all markers in our tour array
      info_content[poiId] = '<span class="marker_edit_image"><img src="'+image+'""/></span><span class="marker_content"><span class="marker_edit_name">' + poi_name + '</span> | <span class="marker_edit_year"> ' + poi_year + '</span></span>';
      allTourMarker.push(Drupal.futurehistoryTourEditMap.marker);

      var bounds = new google.maps.LatLngBounds();
      for (var c = 0; c < allTourMarker.length; c++) {
       bounds.extend(allTourMarker[c].getPosition());
      }
      Drupal.futurehistoryTourEditMap.map.fitBounds(bounds);
    }
  }

  // hover the thumnail images
  function hoverThumb(action, id) {
    var elementToChange = $('#'+id).find('img');
    if (action == 'hover') {
      elementToChange.css('box-shadow','3px 3px 4px #992683');
    } else {
      elementToChange.css('box-shadow', 'none');
    }
  }

  // hover the map marker

  function hoverMarker(action, id) {
    var infoBoxOptions = {
         //content: 'dummy'
        disableAutoPan: false
        ,maxWidth: 0
        ,pixelOffset: new google.maps.Size(0, 0)
        ,zIndex: null
        ,boxStyle: {
          background: "#ffffff"
          ,opacity: 0.85
          ,width: "270px"
         }
        ,closeBoxMargin: "10px 2px 2px 2px"
        ,closeBoxURL: ""
        ,infoBoxClearance: new google.maps.Size(1, 1)
        ,isHidden: false
        ,pane: "floatPane"
        ,enableEventPropagation: false
      };
      infoBox.setOptions(infoBoxOptions)

    for ( var i = 0; i< allTourMarker.length; i++) {
      if (id === allTourMarker[i].id) {

        if (action == 'hover'){
          infoBox.setContent(info_content[id]);
          infoBox.open(Drupal.futurehistoryTourEditMap.map, allTourMarker[i]);
          allTourMarker[i].setIcon(fh_marker_violet);
          break;
        }
        else {
          infoBox.close(Drupal.futurehistoryTourEditMap.map, allTourMarker[i]);
          allTourMarker[i].setIcon(fh_marker_blue);
          break;
        }
      }
    }
  }



  //Start drupal behaviors for tour map
  Drupal.behaviors.futurehistoryTourEditMap = {
    attach: function (context, settings) {

      // Touren Map STUFF
      $('#futurehistory-tour-edit-map', context).each(function() {
        var $this = $(this);


        Drupal.futurehistoryTourEditMap = {};
        mapZoom = 16;

        if (mapCenter == undefined) {
          var initial_center_lat = 51.31491849367987;
          var initial_center_lng = 9.460614849999956;
          mapCenter =  new google.maps.LatLng(initial_center_lat,initial_center_lng);
          mapZoom = 6;
        }

        Drupal.futurehistoryTourEditMap.map = new google.maps.Map(this, {
          center: mapCenter,
          zoom: mapZoom,
          mapTypeId: google.maps.MapTypeId.ROADMAP,
          mapTypeControl: false,
          zoomControl: true,
          streetViewControl:false,
          rotateControl:false,
          scrollwheel: false,
        });

        // set tilt to 0 and stop rotatign the map
        Drupal.futurehistoryTourEditMap.map.setTilt(0);
        showTourOnMap();



        Drupal.tableDrag.prototype.onDrop = function () {
          for (var i = 0; i < allTourMarker.length; i++) {
            allTourMarker[i].setMap(null);
          }
          allTourMarker = [];
          showTourOnMap();
        }

        //hover the pois function
         var poi_id;
         $('#entry-order tr').mouseover(function() {
           poi_id = $(this).attr('id');
           hoverMarker('hover', poi_id);
           hoverThumb('hover',poi_id);

         }).mouseout(function() {
           hoverMarker('out', poi_id);
           hoverThumb('out',poi_id);
         });

      }); // end MAP each function

      // if (initTourDistance < maxTourDistance) {
      //   $( '#futurehistory-tour-edit-map').before( '<p id="tour_warning">Tour Distanz ist größer als 10 000m - es wird keine Route eingezeichnet</p>');
      // }

    }  // end beaviors and atach function
  }
})(jQuery);
