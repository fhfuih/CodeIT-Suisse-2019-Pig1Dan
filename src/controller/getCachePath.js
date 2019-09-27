const path = require('path');

function getCachePath() {
  return path.join(__dirname, '..', '..', 'cache', Date.now());
}

module.exports = getCachePath;
