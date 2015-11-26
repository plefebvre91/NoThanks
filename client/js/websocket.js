if(!window.WebSocket)
    throw "Impossible d'utiliser WebSocket. Votre navigateur ne connait pas cette classe.";

var ws = new WebSocket("ws://localhost:9001/");

ws.onopen = function(e){$('#title').html("OK"); ws.send('LOL');}
ws.onmessage = function(e){console.log(e.data)
			  Object player = JSON.parse(e.data);} 
ws.onclose = function(e){$("#title").html("Close");}
ws.onerror = function(e){console.log('Erreur websocket');}

//socket.close();

function ws_send(msg){
    var i=0;
    if(ws.readyState != 1){
	$("#title").html("Autre essai" + i);
	setTimeout(send(msg), 400);
	i++;
    }
    else  ws.send(msg);
}
