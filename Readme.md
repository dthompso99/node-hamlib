# node-hamlib

node-hamlib is a simple wrapper around https://hamlib.github.io/ for control of an amateur radio via nodejs.  It was designed to run on a raspberry pi, but it should compile on any linux platform (I'll work on windows). 


# System Requirements

You'll need `libhamlib-dev` and all of its pre-requisites in order to link up and build correctly.  You'll also need node-gyp as this is compiled at install time

new requirements: `portaudio19-dev`

## Simple Example

```
const nodeham = require('../build/Release/hamlib');
const test = new nodeham.HamLib(1035, 1);
test.open();
console.log('get vfo', test.getVfo());
console.log('get frequency', test.getFrequency());
console.log('get mode', test.getMode());
console.log('get strength', test.getStrength())
```


### Docs
`Constructor`: 
    construct a new hamlib instance.  Takes the radio model as a constructor
    execute `rigctl -l` to find your rig model number (working on a command for that)
    `new HamLib(1035)`

`.open()`:
    opens the serial or usb connection to the rig, must be called before other actions

`.setVfo("VFO-A")`
    on radios that support it, switches the active vfo to `VFO-A` and `VFO-B` (991 does not)

`.setFrequency(144390000)`
    sets the frequency to the specified integer, in hertz

`.setMode('PKTFM')`
    sets the mode of the radio, ie USB, LSB, FM

`.setPtt(true)`
    toggles PTT of the radio on (true) and off (false)

`.getVfo()`
    returns the current VFO on radios that support it

`.getFrequency()`
    returns the current frequency of the connected rig

`.getMode()`
    returns the current mode of the connected rig
    
`.getStrength()`
    returns the current signal strength of the connected rig

`.close()`
    disconnect from the rig, but not destroy the object.  call `.open()` again to re-establish

`.destroy()`
    destroy the connection to the rig.  you should `delete` the refrence to hamlib after calling delete to encourage gc to happen    

### TODO
This is a work in progress, documentation will be updated as its developed!

I expect issues with initalizing non-usb radios, I'll re-work the constructor as soon as i can set up a test