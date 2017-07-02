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

var ws = new WebSocket("ws://localhost:8080/nthx");

ws.onclose = function(e) {
    $("#title").html("Close");
};


ws.onerror = function(e){
    $("#title").html("Close");
    console.log('Erreur websocket');
    ws.close();
};

var cardOnTop = "resources/img/cards/no.png";
var cards = [];
var score = 0;
var coins = 11;
var name="no_name";

ws.onmessage = function(e){
    console.log(e.data);
    var response;
    response = JSON.parse(String(e.data));
    if(response.hasOwnProperty("card"))
    {
	console.log(response.card);
	cardOnTop = response.card;
    }
    if(response.hasOwnProperty("cards"))
    {
	console.log(response.cards);
	cards = response.cards;
    }
    if(response.hasOwnProperty("score"))
    {
	console.log(response.score);
	score = response.score;
    }
    if(response.hasOwnProperty("coins"))
    {
	console.log(response.coins);
	coins = response.coins;
    }
    if(response.hasOwnProperty("name"))
    {
	console.log(response.name);
	name = response.name;
    }
    if(response.hasOwnProperty("status"))
    {
	console.log(response.status);
	setStatus(response.status);
    }    
};


/**
 * Game creation module controller
 */
app.controller('GameCreationCtrl', 
	       ['$scope','$timeout',
		
		function($scope, $timeout) {
		    ws.onopen = function(e){
			$("#title").html("OK");
			$scope.setStatus(MSG_CONNECTED);
		    };

		    $scope.send = function(msg) {
			var i=0;
			if($scope.ws.readyState != 1){
			    $("#title").html("Tentative " + i);
			    setTimeout(function(){
				$scope.send(msg)
			    },500);
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
			    cards: []
			},
			{
			    name: $scope.names[1],
			    type: TYPE_HUMAN,
			    score:0,
			    coins:11,
			    cards: []
			}];
		    
		    // Add a new player
		    $scope.addPlayer = function(type){
			addPlayer($scope.players,
				  $scope.names,
				  type);
		    };

		    
		    $scope.currentPlayer = $scope.players[0];

		    $scope.play = function(action) {
			ws.send("{\"action\":\"play\",\"param\":\"" + action + "\"}");
			$scope.updatePlayer();
			$scope.getCardOnTop();
			return false;
		    };

		    $scope.cardOnTop = cardOnTop;
		    
		    $scope.getCardOnTop = function(){
			ws.send("{\"action\":\"get\",\"param\":\"card-on-top\"}");
			$timeout(function() {
			    $scope.cardOnTop = cardOnTop;
			},100);			
		    };
		    
		    $scope.updatePlayer = function(){
			ws.send("{\"action\":\"player-info\"}");
			$timeout(function() {
			    $scope.currentPlayer.score = score;
			    $scope.currentPlayer.cards = cards;
			    $scope.currentPlayer.name  = name;
			    $scope.currentPlayer.coins = coins;
			},100);			
		    };
		    
		    // Remove the last player
		    $scope.removePlayer = function() {
			removePlayer($scope.players);
		    };

		    // Enables/disables screen display
		    $scope.showCreationScreen = true;
		    $scope.showScoresScreen = true;
		    $scope.showGameScreen   = true;
		    
		    $scope.showCreation = function(display) {
			$scope.showCreationScreen = display;
		    };
		    
		    $scope.showScores = function(display) {
			$scope.showScoresScreen = display;
		    };
		    
		    $scope.showGame = function(display) {
			$scope.showGameScreen = display;
		    };

		    $scope.updateAll = function(){
			$timeout(function(){
			    $scope.updatePlayer();
			    $scope.getCardOnTop();
			    $scope.updateAll();
			},200);
		    };
		    
		    $scope.createGame = function() {
			_createGame($scope.players);
			
			$scope.showCreation(false);
			$scope.showScores(false);
			$scope.showGame(false);
			$scope.updatePlayer();
			$scope.getCardOnTop();
			$scope.updateAll();
			return false;
		    };
		}]);


function _createGame(players){
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
