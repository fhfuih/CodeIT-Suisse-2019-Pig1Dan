'use strict';

const path = require('path');
const { PythonShell } = require('python-shell');
const getCachePath = require('./getCachePath');
const fs = require('fs');

function technicalAnalysis(req, res) {
  const input = JSON.stringify(req.body);

  const scriptPath = path.join(__dirname, 'technicalAnalysis.py');
  const cachePath = getCachePath();
  fs.writeFileSync(cachePath, input);

  return new Promise((resolve, reject) => {
    let returnValue = '';

    const pyshell = new PythonShell(scriptPath, {
      pythonPath: 'python3',
      args: [cachePath]
    });
    pyshell.on('message', msg => {
      returnValue += msg;
    })
    pyshell.end((err, code, signal) => {
      if (err) {
        return reject(err);
      }
      return resolve(JSON.parse(returnValue));
    })
  }).then(data => res.send(data));
}

module.exports = technicalAnalysis;
