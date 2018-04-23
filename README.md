# opengl-car
A futuristic soapbox car in OpenGL for the course Computergraphics by Herman Crauwels (Campus De Nayer, KU Leuven). This application provides a demo for several OpenGL functions and is written in ANSI C.

## Features
- [x] Basic car
- [x] Basic finish
- [x] Multiple 3D transformations (orthogonal, symmetric, ...)
- [x] Multiple cars on the screen
- [x] Show axes, light sources, ... controlled with a keyboard key
- [x] Improved finish
- [x] 4 different light sources
- [x] Switch between several shade models
- [x] Menu to configure the materials used to create the car
- [x] Keyboard shortcuts
- [x] Animates the wheels of the car
- [x] Texture support of the finish and the car
- [x] Toggle the alpha value of the car
- [ ] Fog support

## Screenshots
WIP

## Shortcuts

### Mouse
- Right click to show the menu where you can select several materials for each component of the car.

- You can also quit the application from the menu if you like.

### Keyboard

<table>
    <tr>
        <th>Key</th>
        <th>Description</th>
    </tr>
    <tr>
        <td>x/X</td>
        <td>Move camera (X axis +/-)</td>
    </tr>
    <tr>
        <td>y/Y</td>
        <td>Move camera (Y axis +/-)</td>
    </tr>
    <tr>
        <td>z/Z</td>
        <td>Move camera (Z axis +/-)</td>
    </tr>
    <tr>
        <td>i</td>
        <td>Move camera to it's initial position</td>
    </tr>
    <tr>
        <td>1</td>
        <td>Toggle ambient light (`GL_LIGHT0`)</td>
    </tr>
    <tr>
        <td>2</td>
        <td>Toggle diffuse light (`GL_LIGHT1`)</td>
    </tr>
    <tr>
        <td>3</td>
        <td>Toggle specular light (`GL_LIGHT2`)</td>
    </tr>
    <tr>
        <td>4</td>
        <td>Toggle spot light (`GL_LIGHT3`)</td>
    </tr>
    <tr>
        <td>s</td>
        <td>Switch to shading mode _SMOOTH_</td>
    </tr>
    <tr>
        <td>S</td>
        <td>Switch to shading mode _FLAT_</td>
    </tr>
    <tr>
        <td>l</td>
        <td>Turn wireframe mode _ON_</td>
    </tr>
    <tr>
        <td>L</td>
        <td>Turn wireframe mode _OFF_</td>
    </tr>
    <tr>
        <td>j</td>
        <td>Turn axes _ON_</td>
    </tr>
    <tr>
        <td>J</td>
        <td>Turn axes _OFF_</td>
    </tr>
    <tr>
        <td>k</td>
        <td>Turn checkpoints _ON_</td>
    </tr>
    <tr>
        <td>K</td>
        <td>Turn checkpoints _OFF_</td>
    </tr>
    <tr>
        <td>g</td>
        <td>Toggle wheel animation</td>
    </tr>
    <tr>
        <td>G</td>
        <td>Toggle car animation</td>
    </tr>
    <tr>
        <td>t</td>
        <td>Toggle textures</td>
    </tr>
    <tr>
        <td>m</td>
        <td>Toggle fog</td>
    </tr>
    <tr>
        <td>n</td>
        <td>Toggle competition mode</td>
    </tr>
    <tr>
        <td>f</td>
        <td>Toggles coachwork transparency</td>
    </tr>
    <tr>
        <td>h/H</td>
        <td>Moves the spot height (+/-)</td>
    </tr>
    <tr>
        <td>v/V</td>
        <td>Manipulates the spot angle (+/-)</td>
    </tr>
    <tr>
        <td>w/W</td>
        <td>Manipulates the spot exponent (+/-)</td>
    </tr>
    <tr>
        <td>b</td>
        <td>Toggles light locking</td>
    </tr>
    <tr>
        <td>e/E</td>
        <td>Manipulates the material shininess (+/-)</td>
    </tr>
    <tr>
        <td>q/Q</td>
        <td>Quits the application</td>
    </tr>
</table>

## License
Everything in this repository is available under the GPLv3 license.
