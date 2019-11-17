# --- Technisch VERSLAG GAMELOOP ---

## 1. Klasses
### Abstracte klassen
Er zijn verschillende abstracte klassen die gebruikt worden als basis om objecten weer te geven en gamemodes te selecteren. De abstracte klassen zijn ScreenObject en MoveableScreenObject

ScreenObject is een klasse die wordt gebruikt voor alle statische objecten zoals hitBoxes in het level.
MovableScreenObject is een realisatie daarvan, maar nog steeds abstract met een extra functie voor bewegende objecten zoals characters.

### Character klasse
De Character klasse is een realisatie van een MoveableScreenObject. De character heeft alle methodes en attributen wat een character moet doen die niet bestuurd wordt door de speler.

### Player klasse
De Player klasse is een generalisatie hiervan. De Player heeft meer functies die gebruikt worden om het object te kunnen besturen. Ook wordt de view van het scherm hierop gecentreerd. Characters worden gebruikt om vijanden te tekenen.

### Weapon klasse
Deze klasse handelt alle interactie met het wapen af. Deze klasse stuurt eventuele informatie door naar de HUD zodat de speler ziet hoeveel munitie hij nog heeft. Elke Player heeft altijd een wapen.



## 2. Graphical User Interface
### Heads Up Display(HUD)
De HUD klasse zorgt ervoor dat alle informatie zichtbaar is voor de speler. De HUD verwerkt inkomende tijd van een server(als die server aanstaat) en laat zien hoeveel kogels de speler nog heeft. Ook zijn de healthpoints zichtbaar.

### Main menu
Deze klasse handelt alles af als een speler in het hoofdmenu zit. Hij kan door middel van de pijltoetsen verschillende opties selecteren.

### Scoreboard
De scoreboard zorgt ervoor dat het voor alle spelers zichtbaar is wat de score is van elke speler. Ook wordt hier bij gehouden hoeveel kills / deaths iemand heeft. Als een speler wordt doodgeschoten, wordt dat naar de server gestuurd en alle andere spelers ontvangen dit. Zo blijft de scoreboard bij iedereen geüpdatet.
 
### TopForceWindow
Dit is een realisatie van een renderwindow. De TopforceWindow handelt extra informatie af zoals een sprite voor de cursor, rotaties en zichtbaarheid van het muisicoon.


## 3. De game loop
De game wordt gestart in het hoofdscherm. De speler kan navigeren door middel van de pijltoetsen. Op dit moment is alleen de “Free for all” geïmplementeerd. Dit is een spelvorm waarbij iedereen voor zichzelf speelt en alle andere spelers moet uitschakelen.
De client maakt vanzelf verbinding met de server. De server bepaald de speeltijd. Als er geen server online is, is de client alleen het level.

De Client bestuurd zijn character(een player object) met de W, A, S en D toetsen. Hij kan herladen met de R knop en schieten met de muis. Het richten gebeurd door middel van een cursor die te besturen is met de muis. Als de speler met de linkermuisknop schiet, is er een lijn zichtbaar waar de kogel zijn eerstvolgende doel treft. Dit kan een speler of een muur zijn. Het is dus niet mogelijk om door muren heen te schieten.

