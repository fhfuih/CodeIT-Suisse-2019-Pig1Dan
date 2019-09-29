const path = require('path');

function getCppExecPath(name, rootname) {
  return path.join(__dirname, '..', '..', 'cpp', rootname || name, name);
}

module.exports = getCppExecPath;
