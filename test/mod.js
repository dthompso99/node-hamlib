const addon = require('../build/Release/hamlib');



console.log(addon.radios())


const test = new addon.HamLib(1035);
console.log(test)
const status = test.open();
//set vfo appears not to work for the 991

//console.log('set vfo(not working): ', test.setVfo('VFO-B'))
console.log('set frequency: ', test.setFrequency(144390000))
console.log('set mode: ', test.setMode('PKTFM', 'narrow'))


console.log('get vfo', test.getVfo());
console.log('get frequency', test.getFrequency());
console.log('get mode', test.getMode());
console.log('get strength', test.getStrength())
test.close();
test.destroy();

/**
test.setPtt(true);
setTimeout(()=> {
    test.setPtt(false);
    test.close();
}, 1000)
 */

// const rig = addon.create(35);
// console.log(rig);
//const rig2 = addon.create(17);
//const test2 = new addon.HamLib(1);
//test2.open();