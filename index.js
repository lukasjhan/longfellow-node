const cm = require('node:module');
const path = require('node:path');
const addonPath = path.join(__dirname, 'build', 'Release', 'longfellow_node.node');
const addon = require(addonPath);

console.log('addon.ping():', addon.ping());
module.exports = addon;