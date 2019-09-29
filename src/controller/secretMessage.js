
function encryption (req, res) {
  const oriArr = req.body;
  const targetArr = [];
  for (let i in oriArr) {
    let strO = oriArr[i].text.toUpperCase();
    let strP = '';
    for (let j = 0; j < strO.length; j += 1) {
      if (strO.charAt(j).match(/[A-Z0-9]/)) {
        strP += strO.charAt(j);
      }
    }
    let strE = [];
    for (let j = 0; j < strP.length; j += 1) {
      strE.push('');
    }
    let start = 0;
    let pointerE = 0;
    let pointerP = 0;
    while (start < oriArr[i].n) {
      strE[pointerE] = strP.charAt(pointerP);
      pointerE += oriArr[i].n;
      pointerP += 1;
      if (pointerE >= strP.length) {
        start += 1;
        pointerE = start;
      }
    }
    targetArr.push(strE.join(''));
  }
  res.send(targetArr);
}

module.exports = encryption;
