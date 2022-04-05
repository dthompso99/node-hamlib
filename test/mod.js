const addon = require('../build/Release/hamlib');


console.log('starting test');
const test = new addon.HamLib(1035, 1);
console.log(test)
const status = test.open();
//set vfo appears not to work for the 991
/*
console.log('set vfo(not working): ', test.setVfo('VFO-B'))
console.log('set frequency: ', test.setFrequency(28350125))
console.log('set mode: ', test.setMode('USB', 'narrow'))
*/

console.log('get vfo', test.getVfo());
console.log('get frequency', test.getFrequency());
console.log('get mode', test.getMode());
console.log('get strength', test.getStrength())
// console.log('status: ', status)
// console.log('hello', addon.hello())
test.setPtt(true);
setTimeout(()=> {
    test.setPtt(false);
}, 1000)

// const rig = addon.create(35);
// console.log(rig);
//const rig2 = addon.create(17);
//const test2 = new addon.HamLib(1);
//test2.open();