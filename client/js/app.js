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

var ws = new WebSocket("ws://localhost:8080/");

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
		    
		    $scope.init=function(){
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
				cards: [4,5,6]
			    },
			    {
				name: $scope.names[1],
				type: TYPE_HUMAN,
				score:0,
				coins:11,
				cards: [7,8,9]
			    }];
			$scope.currentPlayer = $scope.players[0];
			$scope.playerIndex = 0;
			
		    }


		    ws.onopen = function(e){
			$("#title").html("OK");
//			$scope.ws.send('LOL');
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
			console.log("Recu :" + e.data);
			updatePlayers($scope.players, e);
		    };
		    

		    $scope.setStatus = setStatus;
		    
		    
		    
		    
		    // Add a new player
		    $scope.addPlayer = function(type){
			addPlayer($scope.players, $scope.names, type);
		    };


		    $scope.nextPlayer = function(){
			console.log("Apres en: " + angular.toJson($scope.players[$scope.playerIndex]));
			var str = "indice: " + $scope.playerIndex + " / nom: " +   $scope.players[$scope.playerIndex].name;
			$scope.playerIndex++;
			$scope.playerIndex %= $scope.players.length;
			$scope.currentPlayer = $scope.players[$scope.playerIndex];
			ws.send(str);
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
			//$scope.init();
			$scope.showCreation(false);
			$scope.showScores(false);
			$scope.showGame(true);
			return false;
		    }
				
		    $scope.r = ra;
		}]);


function _createGame(players){

    playing = true;
    var data = '{"type":"init","players":' + angular.toJson(players)+'}';
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
