'use strict';

const { spawn } = require('child_process');
const getCppExecPath = require('./getCppExecPath');

function sort(req, res) {
  const input = req.body;
  return new Promise((resolve, reject) => {
    const child = spawn(getCppExecPath('sorting'), [JSON.stringify(input)]);
    child.stdout.on('data', data => resolve(JSON.parse(data.toString()))); // buffer
    child.stderr.on('data', data =>
      reject(new Error(JSON.parse(data.toString())))
    ); // buffer
    child.on(
      'close',
      data =>
        data && reject(new Error(`Alrogithm aborted with exit code (${data})`))
    );
  }).then(data => res.json(data));
}

module.exports = sort;
