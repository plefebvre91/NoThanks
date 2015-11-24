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
	    title: '@',
	    subtitle: '@',
	    name: '@'
	},
	templateUrl : './templates/player-info.html'
    };
});
