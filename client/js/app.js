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

var currentCard = 3;
var names = ['Ahmed', 'Lisa', 
		'Leo', 'Francoise', 'Astrid'];

		
// Players info
var players = [
    {
	name: names[0], 
	type: TYPE_PC, 
	score:0, 
	coins:11,
	cards: [4,5,6]
    },
    {
	name: names[1],
	type: TYPE_PC,
	score:0,
	coins:11,
	cards: [7,8,9]
    }];


var ws = new WebSocket('ws://'+APP_SERVER+':'+APP_PORT+'/');

ws.onclose = function(e) {
    $("#title").html("Close");
};


ws.onerror = function(e){
    $("#title").html("Close");
    console.log('Erreur websocket');
    ws.close();
};


		    
/**
 * Game creation module controller
 */
app.controller('GameCreationCtrl', 
	       ['$scope',
		
		function($scope) {
		    
		    $scope.players = players;
		    $scope.names = names;
		    $scope.init = function(){
			// Players names
			$scope.currentPlayer = players[0];
			$scope.playerIndex = 0;
		    }
		    
		    $scope.update = function(json) {
			var objData = new Object();
			objData = JSON.parse(json.data);
			
			console.log('Recu : ' + angular.toJson(objData));

			$scope.currentCard = objData.top;
			
			for(i=0;i<objData.players.length;i++){
			    players[i].score = objData.players[i].score;
			    players[i].cards = objData.players[i].cards.slice(0);
			    players[i].coins = objData.players[i].coins;
			}
			
			$scope.playerIndex++;
			$scope.playerIndex %= players.length;
			$scope.currentPlayer = players[$scope.playerIndex];
			
			//return false;
		    }

		    ws.onopen = function(e){
			$("#title").html("Running...");
			$scope.init();
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
		    
		    ws.onmessage = function(e){
			$scope.update(e);
		    };
		    		    
		    $scope.setStatus = setStatus;
		    		    
		    // Add a new player
		    $scope.addPlayer = function(type) {addPlayer(players, $scope.names, type);};

		    $scope.nextPlayer = function(){
			console.log("Apres en: " + angular.toJson(players[$scope.playerIndex]));
			$scope.playerIndex++;
			$scope.playerIndex %= players.length;
			$scope.currentPlayer = players[$scope.playerIndex];
//			$scope.currentCard = currentCard;
			
//			while($scope.currentPlayer.type == TYPE_/) ws.send("next");
			//ws.send(str);
			return false;
		    };
		    
		    // Remove the last player
		    $scope.removePlayer = function() {removePlayer(players);};

		    // Enables/disables screen display
		    $scope.showCreationScreen = true;
		    $scope.showScoresScreen = false;
		    $scope.showGameScreen   = false;
		    
		    $scope.showCreation = function(display) {$scope.showCreationScreen = display;};
		    $scope.showScores = function(display)   {$scope.showScoresScreen = display;};
		    $scope.showGame = function(display)     {$scope.showGameScreen = display;};
		    
		    $scope.createGame = function() {
			_createGame(players);
			//$scope.init();

			$scope.showCreation(false);
			$scope.showScores(false);
			$scope.showGame(true);
			return false;
		    }
		}]);


function _createGame(players){

    playing = true;
    var data = '{"phase":"init","players":' + angular.toJson(players)+'}';
    ws.send(data);
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
