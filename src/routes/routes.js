const router = require('express-promise-router')();

const sort = require('../controller/sort');
const square = require('../controller/square');
const genSeq = require('../controller/generateSequence');
const lottery = require('../controller/reverseLottery');
const chessGame = require('../controller/chessgame');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.post('/sort', sort);

router.post('/square', square);

router.post('/generateSequence', genSeq);

router.get('/lottery', lottery);

router.post('/chessgame', chessGame);

module.exports = router;
