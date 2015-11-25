/**
 * Angular application
 */

var app = angular.module('NoThanksApp', []);


/**
 * Menu controller
 */
app.controller('MenuCtrl', ['$scope',
    function($scope) {
	$scope.title = 'No Thanks!';
	$scope.subtitle = 'Version 1.0 for Mobile and Desktop';
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
    {name: 'Ahmed', type: 'Human', score:0, coins:11},
    {name: 'Lisa',  type: 'Human', score:0, coins:11},
];

var ra = [3];
for(i=4;i<26;i++){
    ra.push(i);
}

console.log(ra);
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
		    $scope.r = ra;
		    $scope.showScoresScreen = false;
		    $scope.showGameScreen = false;
		    $scope.showCreateGameScreen = true;
		}]);




$(".game-screen").hide();

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
    p.score = 0;
    p.coins = 11;

    // Add to the players list
    players.push(p);

    return false;
};



function createGame(){
    var data = '{"players":' + angular.toJson(players)+'}';
    
    ws.send(data);

    console.log(data);

    $("#main").animate({opacity: 0.0}, 1000, function() {});
    
    $(".game-screen").animate({opacity: 0.0}, 1000, function() {});


    var audio = new Audio('resources/sound/sound.mp3');
    audio.play();
        
    return false;
}


