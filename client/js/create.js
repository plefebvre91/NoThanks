function create_game(){
    var nbPlayers = 4;
    var names = ['Bob', 'Dylan', 'Margarett', 'Leo']; 
    var types = ['human', 'pc', 'pc', 'pc'];

    var data = '{ "nbPlayers" : '+nbPlayers
	+',names:' + JSON.stringify(names)
	+',types:' + JSON.stringify(types)+'}';
    
    ws.send(data);

    $("#main").animate({opacity: 0.0}, 1000, function() {});

    return false;
}


