const path = require('path');

function getCachePath() {
  return path.join(__dirname, '..', '..', 'cache', Date.now().toString());
}

module.exports = getCachePath;
