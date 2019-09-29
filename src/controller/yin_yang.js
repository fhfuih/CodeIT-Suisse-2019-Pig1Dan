'use strict';

const { spawn } = require('child_process');
const getCppExecPath = require('./getCppExecPath');
const getCachePath = require('./getCachePath');
const fs = require('fs');

function yinyang(req, res) {
  const input = JSON.stringify(req.body);

  const cachePath = getCachePath();
  fs.writeFileSync(cachePath, input);

  return new Promise((resolve, reject) => {
    const child = spawn(getCppExecPath('yin-yang'), [cachePath]);
    let returnValue = Buffer.from([]);

    child.stdout.on('data', data => {
      returnValue = Buffer.concat([returnValue, data]);
    }); // buffer block
    child.stdout.on('close', () => resolve(JSON.parse(returnValue.toString())));

    child.stderr.on('data', data =>
      reject(new Error(JSON.parse(data.toString())))
    ); // buffer

    child.on('close', data => {
      if (data) {
        return reject(new Error(`Alrogithm aborted with exit code (${data})`));
      }
      // else {
      //   return fs.unlink(cachePath);
      // }
    });
  }).then(data => res.json(data));
}

module.exports = yinyang;
