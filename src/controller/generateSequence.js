'use strict';

const { spawn } = require('child_process');
const getCppExecPath = require('./getCppExecPath');

function generateSequence(req, res) {
  const payload = req.body;
  const execPath = getCppExecPath('generateSqeuence');

  return new Promise((resolve, reject) => {
    const child = spawn(execPath);
    const { write } = child.stdin;
    let returnValue = Buffer.from([]);

    child.stdout.on('data', data => {
      returnValue = Buffer.concat([returnValue, data]);
    }); // buffer block
    child.stdout.on('close', () => resolve(returnValue.toString()));

    child.stderr.on('data', data =>
      reject(new Error(JSON.parse(data.toString())))
    ); // buffer

    child.on('close', data => {
      if (data) {
        return reject(new Error(`Alrogithm aborted with exit code (${data})`));
      }
    });

    // stdin
    write(payload.modules.length + '\n');
    payload.modules.forEach(m => write(m + '\n'));
    write(payload.dependencyPairs.legnth + '\n');
    payload.dependencyPairs.forEach(({ dependee, dependentOn }) => {
      write(dependee + '\n' + dependentOn + '\n');
    });
  }).then(data => res.type('json').send(data));
}

module.exports = generateSequence;
