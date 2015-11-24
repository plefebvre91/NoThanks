var app = angular.module('NoThanksApp', []);

app.controller('MenuCtrl', ['$scope',
    function($scope) {
	$scope.title = 'NoThanksApp 1.0';
	$scope.subtitle = 'Create a game';
    }
]);

var names = ['Bob', 'Dylan', 'Margarett', 'Alex', 'Robert'];

var players = [
    {name: 'Bob',       type: 'Human'},
    {name: 'Dylan',     type: 'Human'},
];


app.controller('GameCreationCtrl', 
	       ['$scope',
		
		function($scope) {
		    $scope.title = 'NoThanksApp 1.0';
		    $scope.nbPlayers = 0;
		    $scope.players = players;
		    
		    $scope.addPlayer = addPlayer;
		    
		    $scope.removePlayer = removePlayer;		    
		    $scope.createGame = createGame;
		}]);



app.directive('playerInfo', function() {
    return {
	restrict : 'E',
	controller : 'GameCreationCtrl',
	replace: true,
	transclude: true,
	scope: {
	    name: '@',
	    type: '@'
	},
	templateUrl : './templates/player-info.html'
    };
});


function removePlayer() {
    if(players.length <=2) {
	return;
    }
    players.pop();
    return false;
    console.log($scope.players);
};


function addPlayer(type) {
    if(players.length >= 5) {
	return;
    }
    
    var p = new Object();
    p.name = names[players.length];
    p.type = type;
    players.push(p);

    return false;
    console.log($scope.players);
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


