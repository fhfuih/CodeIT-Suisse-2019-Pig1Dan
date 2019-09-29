'use strict';

function getLowestDigit(n, p) {
  let a = n % 10;
  let b = p;
  let res = 1;
  while (b > 0) {
    if (b % 2 === 1) {
      res = (res * a) % 10;
    }
    a = a * a % 10;
    b = Math.floor(b / 2);
  }
  return res;
}

function exponent(req, res) {
  const {n, p} = req.body;
  if (n === 0) {
    return res.send({
      result: [0, 1, 0]
    });
  }
  const lowestDigit = getLowestDigit(n, p);
  const plogn = p * Math.log10(n);
  const digits = Math.floor(plogn) + 1;
  const highestDigit = Math.floor(Math.pow(10, plogn - digits + 1));
  console.log(`${n}^${p} is [${highestDigit}, ${digits}, ${lowestDigit}]`);
  res.send({
    result: [highestDigit, digits, lowestDigit]
  });
}

module.exports = exponent;
