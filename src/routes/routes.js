const router = require('express-promise-router')();

const sort = require('../controller/sort');
const square = require('../controller/square');
const genSeq = require('../controller/generateSequence');
const lottery = require('../controller/reverseLottery');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.post('/sort', sort);

router.post('/square', square);

router.post('/generateSequence', genSeq);

router.post('/lottery', lottery);

module.exports = router;
