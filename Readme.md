# node-hamlib

node-hamlib is a simple wrapper around https://hamlib.github.io/ for control of an amateur radio via nodejs.  It was designed to run on a raspberry pi, but it should compile on any linux platform (I'll work on windows). 


# System Requirements

You'll need `libhamlib-dev` and all of its pre-requisites in order to link up and build correctly.  You'll also need node-gyp as this is compiled at install time

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

### TODO
This is a work in progress, documentation will be updated as its developed!