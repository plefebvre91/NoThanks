/**
 * Remove last player
 */
function removePlayer(playersArray) {
    if(playersArray.length <=2) {
	return;
    }
    playersArray.pop();

    return false;
};


/**
 * Add a new player
 * \param type 'Computer' or 'Human'
 */
function addPlayer(playersArray, playersNames, type) {
    var nbPlayers = playersArray.length; 
    
    if(nbPlayers >= 5) {
	return;
    }
    
    // Creates new player
    var p = new Object();
    p.name = playersNames[nbPlayers];
    p.type = type;
    p.score = 0;
    p.coins = 11;
    p.cards = [];
    // Add to the players list
    playersArray.push(p);

    return false;
};

function updatePlayers(playersArray, newJsonPlayers){
    var player = new Object();
    player = JSON.parse(newJsonPlayers.data);
    for(i=0;i<player.players.length;i++){
	playersArray[i].score = player.players[i].score;
	console.log("cards: " + angular.toJson(player.players[i].cards));
	playersArray[i].cards = player.players[i].cards.slice(0);
	playersArray[i].coins = player.players[i].coins;
	
	console.log("Changé en: " + angular.toJson(playersArray[i]));
    }

}
