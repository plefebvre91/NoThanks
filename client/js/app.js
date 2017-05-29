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

var ws = new WebSocket("ws://localhost:8080/echo");

ws.onclose = function(e) {
    $("#title").html("Close");
};


ws.onerror = function(e){
    $("#title").html("Close");
    console.log('Erreur websocket');
    ws.close();
};

var cardOnTop = "resources/img/cards/4.png";

ws.onmessage = function(e){
    console.log(e.data);
    var response;
    response = JSON.parse(String(e.data));

    if(response.hasOwnProperty("card"))
    {
	console.log(response.card);
	cardOnTop = response.card;
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
		    
		    $scope.take = function(){
			ws.send("{\"action\":\"play\",\"param\":\"take\"}");
			ws.send("{\"action\":\"get\",\"param\":\"game\"}");
			$scope.getCardOnTop();
			$scope.cardOnTop = cardOnTop;
			return false;
		    };


		    $scope.drop = function(){
			ws.send("{\"action\":\"play\",\"param\":\"drop\"}");
			ws.send("{\"action\":\"get\",\"param\":\"game\"}");
			$scope.getCardOnTop();
			$scope.cardOnTop = cardOnTop;
			return false;
		    };

		    $scope.cardOnTop = "resources/img/cards/4.png";
		    
		    $scope.getCardOnTop = function(){
			ws.send("{\"action\":\"get\",\"param\":\"card-on-top\"}");
			$scope.cardOnTop = cardOnTop;
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
