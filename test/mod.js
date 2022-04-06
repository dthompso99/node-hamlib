const radio = require('../build/Release/hamlib');



//console.log(addon.radios())


const ctrl = new radio.HamLib(1035);
console.log(ctrl)
const status = ctrl.open();
//set vfo appears not to work for the 991

//console.log('set vfo(not working): ', ctrl.setVfo('VFO-B'))
//console.log('set frequency: ', ctrl.setFrequency(144390000))
//console.log('set mode: ', ctrl.setMode('PKTFM', 'narrow'))


console.log('get vfo', ctrl.getVfo());
console.log('get frequency', ctrl.getFrequency());
console.log('get mode', ctrl.getMode());
console.log('get strength', ctrl.getStrength())
ctrl.close();
ctrl.destroy();


const decoder = new radio.Decoder();
decoder.open();
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