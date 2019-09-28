'use strict';

const getInt = () => Math.round(Math.random() * 100 + 1);

function reverseLottery(req, res) {
  const arr = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
  res.send(arr);
}

module.exports = reverseLottery;
