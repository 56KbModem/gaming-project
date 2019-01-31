# --- TECHNISCH VERSLAG NETWORKED GAME ---

## Inleiding:
Vanaf het begin van het ontwikkelen van de game was
voor ons het belang om multiplayer te implementeren
aanwezig. Topforce is een top-down shooter voor Mac
en Windows, dus om met twee man of meer achter 1 
laptop zitten is mogelijk maar niet erg handig om
twee redenen, ten eerste zit je dicht op elkaar en
ten tweede kan je op elkaars scherm kijken mochten
wij de multiplayer implementeren als split-screen.

Topforce zijn multiplayer modus (modus..., eigenlijk
de enige modus die hij bevat) zou dus via het netwerk
geimplemeteerd moeten worden. Het was de bedoeling
dat er een dedicated server kwam om de uitwisseling
van netwerk data en de game logica zo veel mogelijk
gescheiden te houden. Een client speelt dus alleen de
game en heeft verbinding met 1 dedicated server i.p.v.
dat een client een eigen server kan hosten.


### 1. UDP vs TCP
Het Topforce protocol is geimplemeteerd bovenop UDP.
Er is voor UDP gekozen omdat het een zeer simpel en
vooral connectieloos protocol is. Aan de ene kant
weet je dan nooit zeker of een datagram in de goede
volgorde aankomt en of deze uberhaupt wel aankomt,
aan de andere kant is dit voor een videogame ook 
niet heel belangrijk en kan het juist schadelijk 
zijn voor de performance. Liever een klein beetje
packet loss in plaats van een hoop overhead uit een
TCP packet.


### 2. Topforce protocol
De (dedicated) server houdt de speeltijd bij aan de
hand van een SFML Clock klasse die elke seconde een
signaal geeft dat er een TimePacket geconstruuerd
en verstuurd moet worden. de form van dit packet is
als volgt:
```cpp
struct TimePacket {
	std::string header;
	int minutes;
	int seconds;
};
```
Elk packet heeft een header (std::string) bovenaan
de datastructuur die gechekt kan worden zodat client
en server weten om welke soort packet het gaat en
deze op de juiste manier geparsed kan worden. De
client verwerkt dit packet door de tijd data, namelijk
de twee integers minutes en seconds om te zetten in
een formaat dat door de HUD klasse getoond kan worden
op het beeldscherm van de speler.

Een ander heel belangrijk packet is de PlayerPacket:
```cpp
struct PlayerPacket {
	std::string header;
	std::string playerName;
	sf::Vector2f position;
	float rotation;
	bool walking;
	bool firing = false;
	sf::Uint32 PlayerId = 0;
	sf::Vector2f firePos;
};
```
Dit packet behelst de data van een speler in de
game. Elk frame wordt de input verwerkt, het 
scherm gerenderd en getekend en de game logica
afgehandeld. Tegelijkertijd wordt er data van
een speler in de PlayerPacket structuur gemaakt
zoals de positie op het veld, zijn rotatie, of de
speler schiet of niet etc. Deze data wordt naar de
dedicated server gestuurd, die de packet relayed
naar alle andere clients die hij kent (lees verder
onder Hoofdstuk 3).

Als een client merkt dat hij een andere speler
geraakt heeft, zal hij een DamagePacket versturen met
de hoeveelheid damage, en welke speler geraakt is door
welke speler. Het packet ziet er als volgt uit:
```cpp
struct DamagePacket{
	std::string header;
	bool died;
	sf::Uint32 hitById;
	std::string hitByName;
	sf::Uint32 playerId;
	std::string playerName;
	unsigned int damage;
};
```
Een speler die een damage packet ontvangt waarbij de 
playerID overeenkomt met zijn eigen playerID zal de
damage van zijn health aftrekken en als deze kleiner
of gelijk is aan 0 zal hij een IDied packet sturen 
naar alle andere spelers (via de server) om aan te
geven dat iemand een kill heeft gemaakt. Aan de hand
van het IDied packet kunnen de spelers hun scoreboard
updaten. Het IDied packet is niets meer dan een
DamagePacket waarbij de unsigned int damage op
0 is gezet.


### 3. Server
De server is gebouwd bovenop een SFML UDP-socket.
Omdat UDP connectieloos is houden we voor elke speler
die een connectie maakt het IP-adres zelf bij,
zodat we weten naar welk adres we data mogen verzenden.
De server houdt de speeltijd bij, deze wordt doorgegeven
aan de server via command-line argumenten, eerst het
aantal minuten en dan de seconden gescheiden door een
spatie. Er kan maximaal een uur gespeeld worden want
een te groot getal wordt in de constructor van
de server teruggezet naar 59, (zowel minuten
als seconden).

Als er niet genoeg of foutieve argumenten aan de 
server gegeven worden dan zal deze niet starten maar
een error message op de stderr stream geven.

Omdat wij de server zo snel mogelijk willen houden
zorgen we ervoor dat deze alleen TimePackets en
PlayerPackets verzend, en verder zo min mogelijk
logica heeft. De server is simpelweg een doorgeef-
luik voor PlayerPackets, zodat spelers elkanders
karakter kunnen renderen op het eigen scherm.

De tijd wordt door de server bijgehouden door
elke seconde een SFML Clock te pollen of er 1
seconde verstreken is, zijn interne seconden
worden dan afgetrokken en zodra de seconden onder
de 0 komen worden ze gereset naar 59 en wordt
er 1 minuut afgetrokken. deze nieuwe tijd wordt
dan verzonden naar de spelers:
```cpp
--secondToPlay;
if (secondToPlay <= 0 && minuteToPlay > 0) {
	--minuteToPlay;
	secondToPlay = 59;
```

