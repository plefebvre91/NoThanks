/**
 * Angular application
 */
var app = angular.module('NoThanksApp', []);

const APP_TITLE    = "Non merci!";
const APP_SUBTITLE = "Version 1";
const TYPE_HUMAN   = 'Human';
const TYPE_PC      = 'Computer';

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


/**
 * Game creation module controller
 */
app.controller('GameCreationCtrl', 
	       ['$scope',
		
		function($scope) {
		    // Players names
		    $scope.names = ['Ahmed', 'Lisa', 
				    'Leo', 'Francoise', 'Astrid'];
		    
		    // Players info
		    $scope.players = [
			{
			    name: $scope.names[0], 
			    type: TYPE_HUMAN, 
			    score:0, 
			    coins:11
			},
			{
			    name: $scope.names[1],
			    type: TYPE_HUMAN,
			    score:0,
			    coins:11
			}];
		    
		    // Add a new player
		    $scope.addPlayer = function(type){
			addPlayer($scope.players, $scope.names, type);
		    };

		    
		    // Remove the last player
		    $scope.removePlayer = function() {
			removePlayer($scope.players);
		    };

		    // Enables/disables screen display
		    console.log("appel");
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
    var data = '{"players":' + angular.toJson(players)+'}';
    ws.send(data);
    console.log(data);
    var audio = new Audio('resources/sound/sound.mp3');
    audio.play();
    return false;
}
