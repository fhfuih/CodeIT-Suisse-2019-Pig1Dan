
var svgson = require('svgson');
var fs = require('fs');
function findArea(source, elements) {
  const {
    cx,
    r
  } = source;
  const sourceX1 = cx - r;
  const sourceX2 = cx + r;
  // console.log('circleCenter:', sourceX1, sourceX2, elements);
  for (let i in elements) {
    const x1 = elements[i].name === 'bucket' ? elements[i].attributes.points[0][0] : (elements[i].attributes.points[0][0] > elements[i].attributes.points[1][0] ? elements[i].attributes.points[1][0] : elements[i].attributes.points[0][0]);
    const x2 = elements[i].name === 'bucket' ? elements[i].attributes.points[2][0] : (elements[i].attributes.points[0][0] < elements[i].attributes.points[1][0] ? elements[i].attributes.points[0][0] : elements[i].attributes.points[0][0]);
    if ((sourceX1 >= x1 && sourceX1 <= x2) || (sourceX2 >= x1 && sourceX2 <= x2)) {
      if (!elements[i].checked) {
        elements[i].checked = true;
        // console.log(elements);
        if (elements[i].name === 'bucket') {
          const width = elements[i].attributes.points[2][0] - elements[i].attributes.points[0][0] - 1;
          const height = elements[i].attributes.points[1][1] - elements[i].attributes.points[0][1];
          // console.log('area:',width * height);
          if (i === elements.length - 1) {
            return width * height;
          } else {
            return (width * height) + findArea({cx: x1, r: 0}, elements.slice(i + 1, elements.length)) + findArea({cx: x2, r: 0}, elements.slice(i + 1, elements.length));
          }
        } else if (elements[i].name === 'pipe') {
          if (i === elements.length - 1) {
            return 0;
          } else {
            const y1 = (x1 === elements[i].attributes.points[0][0] ? elements[i].attributes.points[0][1] : elements[i].attributes.points[1][1]);
            const y2 = (x2 === elements[i].attributes.points[0][0] ? elements[i].attributes.points[0][1] : elements[i].attributes.points[1][1]);
            return findArea({cx: (y1 < y2 ? x2 : x1), r: 0}, elements.slice(i + 1, elements.length));
          }
        }
      } else {
        return 0;
      }
    }
  }
  return 0;
}
async function bucketFill(req, res) {
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
  // svgObj.children.sort((a, b) => {
  //   if (a.name === 'circle') {
  //     a.y = parseInt(a.attributes.cy);
  //   } else {
  //     a.y = parseInt(a.attributes.points[0][1]);
  //   }
  //   if (b.name === 'circle') {
  //     b.y = parseInt(b.attributes.cy);
  //   } else {
  //     b.y = parseInt(b.attributes.points[0][1]);
  //   }
  //   return a.y - b.y;
  // });
  // const elements = svgObj.children;
  // for (let c in circles) {
  //   elements.shift();
  // }
  // for (let c in circles) {
  //   let shiftNum = 0;
  //   const elementsCopy = elements.slice(0);
  //   for (let i in elementsCopy) {
  //     if (elementsCopy[i].name === 'bucket') {
  //       if (elementsCopy[i].attributes.points[1][1] <= circles[c].circleY) {
  //         shiftNum += 1;
  //       }
  //     } else if (elementsCopy.name === 'pipe') {
  //       let leftUp = elementsCopy[i].attributes.points[0][0] < elementsCopy[i].attributes.points[1][0] ? (elementsCopy[i].attributes.points[0][1] < elementsCopy[i].attributes.points[1][1]) : (elementsCopy[i].attributes.points[0][1] > elementsCopy[i].attributes.points[1][1]);
  //       let bottom = Math.max(elementsCopy[i].attributes.points[1][1], elementsCopy[i].attributes.points[0][1]);
  //       let left = Math.min(elementsCopy[i].attributes.points[0][0], elementsCopy[i].attributes.points[1][0]);
  //       let right = Math.max(elementsCopy[i].attributes.points[0][0], elementsCopy[i].attributes.points[1][0]);
  //       if (leftUp) {
  //         if (bottom - Math.abs(right - circles[c].circleX) < circles[c].circleY) {
  //           shiftNum += 1;
  //         }
  //       } else {
  //         if (bottom - Math.abs(left - circles[c].circleX) < circles[c].circleY) {
  //           shiftNum += 1;
  //         }
  //       }
  //     }
  //   }
  //   while (shiftNum > 0) {
  //     elementsCopy.shift();
  //     shiftNum -= 1;
  //   }
  //   area += findArea({cx: circles[c].circleX, r: circles[c].circleR}, elementsCopy)
  // }
  res.send(svgPass);
}

module.exports = bucketFill;
