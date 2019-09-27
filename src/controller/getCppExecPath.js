const path = require('path');

function getCppExecPath(name) {
  return path.join(__dirname, '..', '..', 'cpp', name, name);
}

module.exports = getCppExecPath;
