'use strict';

const testAddon = require('../../build/Release/testaddon.node');

function helloWorldCpp(req, res) {
  const { name = 'World' } = req.query;
  console.log(testAddon);
  res.send(testAddon.hello(name));
}

module.exports = helloWorldCpp;
