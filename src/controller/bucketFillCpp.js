
const svgson = require('svgson');
const { spawn } = require('child_process');
const getCppExecPath = require('./getCppExecPath');
const getCachePath = require('./getCachePath');
const fs = require('fs');

async function bucketFillCpp(req, res) {
  const svgTxt = req.body;
  const svgObj = await svgson.parse(svgTxt);
  const svgPass = {
    bck: [],
    pipe: [],
    source: []
  }
  let area = 0;
  const circles = [];
  for (let i in svgObj.children) {
    if (svgObj.children[i].name !== 'circle') {
      svgObj.children[i].attributes.points = svgObj.children[i].attributes.points.split(' ');
      for (let j in svgObj.children[i].attributes.points) {
        svgObj.children[i].attributes.points[j] = svgObj.children[i].attributes.points[j].split(',');
        svgObj.children[i].attributes.points[j][0] = parseInt(svgObj.children[i].attributes.points[j][0]);
        svgObj.children[i].attributes.points[j][1] = parseInt(svgObj.children[i].attributes.points[j][1]);
      }
      if (svgObj.children[i].attributes.points.length === 2) {
        svgObj.children[i].name = 'pipe';
        svgPass.pipe.push({
          low: {
            x: svgObj.children[i].attributes.points[0][0],
            y: svgObj.children[i].attributes.points[0][1],
          },
          high: {
            x: svgObj.children[i].attributes.points[1][0],
            y: svgObj.children[i].attributes.points[1][1],
          },
        });
      } else {
        svgObj.children[i].name = 'bucket';
        svgPass.bck.push({
          x_left: Math.min(svgObj.children[i].attributes.points[0][0], svgObj.children[i].attributes.points[2][0]),
          x_right: Math.max(svgObj.children[i].attributes.points[0][0], svgObj.children[i].attributes.points[2][0]),
          y_low: Math.max(svgObj.children[i].attributes.points[0][1], svgObj.children[i].attributes.points[1][1]),
          y_high: Math.min(svgObj.children[i].attributes.points[0][1], svgObj.children[i].attributes.points[1][1]),
        });
      }
      svgObj.children[i].checked = false;
      if (svgObj.children[i].name === 'bucket') {
        svgObj.children[i].fill = false;
      }
    } else {
      circles.push({
        circleX: parseInt(svgObj.children[i].attributes.cx),
        circleY: parseInt(svgObj.children[i].attributes.cy),
        circleR: parseInt(svgObj.children[i].attributes.r)
      });
      svgObj.children[i].checked = true;
      svgPass.source.push({
        x: parseInt(svgObj.children[i].attributes.cx),
        y: parseInt(svgObj.children[i].attributes.cy)
      })
    }
  }

  const input = JSON.stringify(svgPass);
  const cachePath = getCachePath();
  fs.writeFileSync(cachePath, input);
  console.log(input);

  return new Promise((resolve, reject) => {
    const child = spawn(getCppExecPath('bucket', 'bucket'), [cachePath]);
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

module.exports = bucketFillCpp;
