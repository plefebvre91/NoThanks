/**
 * Angular directive for player information display
 */
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


/**
 * Angular directive for scores display
 */
app.directive('playerScore', function() {
    return {
	restrict : 'E',
	controller : 'GameCreationCtrl',
	replace: true,
	transclude: true,
	scope: {
	    name: '@',
	    score: '@'
	},
	templateUrl : './templates/player-score.html'
    };
});

