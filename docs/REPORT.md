# Zeepkist
- __Naam__: Dylan Van Assche
- __Datum__: 24 mei 2018
- __Repository__: [https://www.github.com/DylanVanAssche/opengl-car](https://www.github.com/DylanVanAssche/opengl-car)

Futuristische zeepkist in OpenGL voor het vak Computergrafieken van Herman Crauwels (Campus De Nayer, KU Leuven) geschreven in ANSI C.

## Features
- [x] Basis zeepkist
- [x] Basic aankomst
- [x] Meerdere 3D transformaties (orthogonaal, symmetrisch, ...)
- [x] Wedstrijd modus
- [x] Assen, lichtbronnen posities, controlepunten, ... kunnen getoond worden
- [x] Uitgebreide aankomst
- [x] 4 verschillende soorten lichtbronnen
- [x] Kiezen van shading modus
- [x] Menu om de materialen en kleuren te configureren van de zeepkist
- [x] Toetsenbord snelkoppelingen
- [x] Animatie van de zeepkist
- [x] Texturen op aankomst, wielen, ...
- [x] Glas modus om het onderstel te kunnen zien
- [x] Mist

## Functies

Bekijk de inline commentaar van de source code om de beschrijving te lezen van de
verschillende argumenten van elke functie.

### car.c
- `void menu(GLint id)`: Hoofdmenu callback welke de dispatching regelt voor andere
submenu's en de quit optie afhandelt.
- `void coachworkMenu(GLint id)`: Carrosserie menu om de kleuren ervan te kiezen.
- `void suspensionMenu(GLint id)`: Onderstel menu om de kleuren ervan te kiezen.
- `void finishMenu(GLint id)`: Aankomst menu om de kleuren ervan te kiezen.
- `void init(void)`: Init functie om verscheidene zaken te initialiseren vooraleer de
OpenGL main loop start
- `void animation(GLint value)`: Callback voor `glutTimerFunc` animatie van de zeepkist
- `void keyboardWatcher(unsigned char key, int x, int y)`: Toetsenbord callback
- `void displayFunction(void)`: Teken callback
- `void windowFunction(GLint newWidth, GLint newHeight)`: Scherm callback
- `int main(int argc, char* argv[])`: Main functie

### finish.c
- `void _drawFinishPart(GLint wireFrame)`: Private functie om 1/4 van de aankomstboog te tekenen.
- `void drawFinish(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLuint textureAddressing[], GLint texture, GLint checkpoints)`: Tekent de volledige aankomstboog.

### vehicle.c
- `void drawSuspension(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular)`: Tekent het onderstel
- `void drawTires(GLint wireFrame, GLfloat animationAngle, GLuint textureAddressing[], GLint texture)`: Tekent de wielen van de zeepkist
- `void drawCoachwork(GLint wireFrame, GLfloat* ambient, GLfloat* diffuse, GLfloat* specular, GLint clear, GLint checkpoints, GLint texture)`: Tekent de carrosserie

### view.c
- `void drawAxes(GLint axes)`: Tekent de assen: X, Y en Z.
- `void drawCheckpoint(const GLfloat* color)`: Tekent een enkel controlepunt, gebruikt door
o.a. de complexe oppervlakten en lichtbronnen positie.
- `void configureLights(GLint ambientLight, GLint diffuseLight, GLint specularLight, GLint spotLight, GLint spotAngle, GLint spotExponent, GLint spotHeight, GLint drawPositions)`: Configueert de lichtbronnen.
- `void configureFog(GLint fog, GLint fogMode, GLfloat far)`: Stelt de mist in en zijn modus.

## Snelkoppelingen

### Muis
- Rechtermuisknop toont een menu waar de kleuren van de verschillende delen van de zeepkist gekozen kunnen worden.

- Je kan de applicatie ook afsluiten als je dat wenst.

### Toetsenbord

| Toets | Beschrijving                                 |
|:-----:| -------------------------------------------- |
| x/X   | Verplaats camera (X as +/-)                  |
| y/Y   | Verplaats camera (Y as +/-)                  |
| z/Z   | Verplaats camera (Z as +/-)                  |
| i     | Verplaats camera naar zijn originele positie |
| 1     | Toggle ambient licht (GL_LIGHT0)             |
| 2     | Toggle diffuse licht (GL_LIGHT1)             |
| 3     | Toggle specular licht (GL_LIGHT2)            |
| 4     | Toggle spot licht (GL_LIGHT3)                |
| s     | Schakel over naar shading mode _SMOOTH_      |
| S     | Schakel over naar shading mode _FLAT_        |
| l     | Schakel wireframe modus_AAN_                 |
| L     | Schakel wireframe modus _UIT_                |
| j     | Toon assen                                   |
| J     | Toon assen niet                              |
| p     | Toon licht posities                          |
| P     | Toon licht posities niet                     |
| k     | Schakel controlepunten _ON_                  |
| K     | Schakel controlepunten _OFF_                 |
| g     | Toggle wiel animatie                         |
| G     | Toggle zeepkist animatie                     |
| t     | Toggle texturen                              |
| m     | Toggle mist                                  |
| M     | Toggle mist modus (_LINEAR / EXP_)           |
| n     | Toggle wedstrijd modus                       |
| f     | Toggle carrosserie doorzichtigheid           |
| h/H   | Manipuleer de spot hoogte (+/-)              |
| v/V   | Manipuleer de spot hoek (+/-)                |
| w/W   | Manipuleer de spot exponent (+/-)            |
| b     | Toggle licht vergrendeling                   |
| e/E   | Manipuleer de materiaal shininess (+/-)      |
| q/Q   | Verlaat de applicatie                        |

## Buildinstructies

1. Clone het repository: `git clone https://github.com/DylanVanAssche/opengl-car.git`
2. Ga in de map: `cd opengl-car`
3. Installeer alle OpenGL afhankelijkheden, je kan deze terugvinden in de `makefile`.
4. Voer `make` uit in de projectmap.
5. Voer `./car` uit om de zeepkist te starten.

_Opmerking_: `-std=c99` optie is nodig om de zeepkist te compileren op moderne systemen. Het kan zijn dat dit een probleem geeft op de HPUX Laurel. De `makefile` is voorzien voor beide systemen, je hoeft enkel de juiste in commentaar te zetten.
