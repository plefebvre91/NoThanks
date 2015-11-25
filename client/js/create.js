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

    // Add to the players list
    playersArray.push(p);

    return false;
};
