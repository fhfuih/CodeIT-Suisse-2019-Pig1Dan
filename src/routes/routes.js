const router = require('express-promise-router')();

const logger = require('../logger/logger');
const sort = require('../controller/sort');
const square = require('../controller/square');
const chessGame = require('../controller/chessGame');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.post('/sort', sort);

router.post('/square', square);

router.post('/chessgame', chessGame);

module.exports = router;
