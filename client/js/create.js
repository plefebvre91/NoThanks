/**
 * Angular application
 */

var app = angular.module('NoThanksApp', []);


/**
 * Menu controller
 */
app.controller('MenuCtrl', ['$scope',
    function($scope) {
	$scope.title = 'NoThanksApp 1.0';
	$scope.subtitle = 'Create a game';
    }
]);

/**
 * Players names list
 */
var names = ['Ahmed', 'Lisa', 'Leo', 'Francoise', 'Astrid'];

/**
 * Players list
 */
var players = [
    {name: 'Ahmed',       type: 'Human'},
    {name: 'Lisa',     type: 'Human'},
];

/**
 * Game creation module controller
 */
app.controller('GameCreationCtrl', 
	       ['$scope',
		
		function($scope) {
		    $scope.players = players;
		    $scope.addPlayer = addPlayer;
		    $scope.removePlayer = removePlayer;		    
		    $scope.createGame = createGame;
		}]);



/**
 * Menu controller
 */
app.controller('ScoresMenuCtrl', 
	       ['$scope',
		function($scope) {
		    
		}
	       ]);


/**
 * Remove last player
 */
function removePlayer() {
    if(players.length <=2) {
	return;
    }
    players.pop();

    return false;
};


/**
 * Add a new player
 * \param type 'Computer' or 'Human'
 */
function addPlayer(type) {
    if(players.length >= 5) {
	return;
    }
    
    // Creates new player
    var p = new Object();
    p.name = names[players.length];
    p.type = type;
    
    // Add to the players list
    players.push(p);

    return false;
};



function createGame(){
    var data = '{"players":' + angular.toJson(players)+'}';
    
    ws.send(data);

    console.log(data);

    $("#main").animate({opacity: 0.0}, 1000, function() {});
    var audio = new Audio('resources/sound/sound.mp3');
    audio.play();
    return false;
}


