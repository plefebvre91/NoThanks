/**
 * Angular application
 */
var app = angular.module('NoThanksApp', []);

if(!window.WebSocket)
    throw "WebSocket indisponible.";



/**
 * Menu controller
 */
app.controller('MenuCtrl', 
	       ['$scope',
		function($scope) {
		    $scope.title = APP_TITLE;
		    $scope.subtitle = APP_SUBTITLE;
		}
	       ]);

var ra = [3];
for(i=4;i<26;i++){
    ra.push(i);
}

var playing = false;

var ws = new WebSocket("ws://localhost:9001/");

ws.onclose = function(e) {
    $("#title").html("Close");
};


ws.onerror = function(e){
    $("#title").html("Close");
    console.log('Erreur websocket');
    ws.close();
};

ws.onmessage = function(e){
    console.log(e.data);
    alert('a');
    if(playing){
	var player = new Object();
	player = JSON.parse(e.data);
	for(i=0;i<players.length;i++){
	    players[i] = player[i];
	}
    }
};

		    
/**
 * Game creation module controller
 */
app.controller('GameCreationCtrl', 
	       ['$scope',
		
		function($scope) {
		    
		    
		    
		    ws.onopen = function(e){
			$("#title").html("OK");
//			$scope.ws.send('LOL');
			$scope.setStatus(MSG_CONNECTED);
		    };
		    
		    
		    $scope.send = function(msg) {
			var i=0;
			if($scope.ws.readyState != 1){
			    $("#title").html("Autre essai" + i);
			    setTimeout($scope.send(msg), 400);
			    i++;
			}
			else  $scope.send(msg);
		    };
		    
		    
		    $scope.setStatus = setStatus;
		    
		    
		    
		    // Players names
		    $scope.names = ['Ahmed', 'Lisa', 
				    'Leo', 'Francoise', 'Astrid'];
		    
		    // Players info
		    $scope.players = [
			{
			    name: $scope.names[0], 
			    type: TYPE_HUMAN, 
			    score:0, 
			    coins:11,
			    cards: [15,10,31]
			},
			{
			    name: $scope.names[1],
			    type: TYPE_HUMAN,
			    score:0,
			    coins:11,
			    cards: [11,21,13]
			}];
		    
		    // Add a new player
		    $scope.addPlayer = function(type){
			addPlayer($scope.players, $scope.names, type);
		    };

		    $scope.currentPlayer = $scope.players[0];
		    $scope.playerIndex = 0;
		    $scope.nextPlayer = function(){
			$scope.playerIndex++;
			$scope.playerIndex %= $scope.players.length;
			$scope.currentPlayer = $scope.players[$scope.playerIndex];
			ws.send("query");
			return false;
		    };
		    
		    // Remove the last player
		    $scope.removePlayer = function() {
			removePlayer($scope.players);
		    };

		    // Enables/disables screen display
		    $scope.showCreationScreen = true;
		    $scope.showScoresScreen = false;
		    $scope.showGameScreen   = false;
		    
		    $scope.showCreation = function(display) {
			$scope.showCreationScreen = display;
		    };
		    
		    $scope.showScores = function(display) {
			$scope.showScoresScreen = display;
		    };
		    
		    $scope.showGame = function(display) {
			$scope.showGameScreen = display;
		    };
		    
		    $scope.createGame = function() {
			_createGame($scope.players);
			$scope.showCreation(false);
			$scope.showScores(false);
			$scope.showGame(true);
			return false;
		    }
				
		    $scope.r = ra;
		}]);


function _createGame(players){
    playing = true;
    var data = '{"players":' + angular.toJson(players)+'}';
//    ws.send(data);
    console.log(data);
    var audio = new Audio('resources/sound/sound.mp3');
    audio.play();
    return false;
}


function setStatus(msg) {
    console.log(msg);
    $(".alert-dismissible").show();
    $("#status").html(msg + '<button type="button" class="close" id="status" data-dismiss="alert" aria-label="Close"> <span aria-hidden="true">&times;</span></button>');
    setTimeout(function(){
	$(".alert-dismissible").hide();
    }, 2000);
}
