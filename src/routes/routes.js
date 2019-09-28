const router = require('express-promise-router')();

const sort = require('../controller/sort');
const square = require('../controller/square');
const genSeq = require('../controller/generateSequence');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.post('/sort', sort);

router.post('/square', square);

router.post(
  '/generateSequence',
  (req, res, next) => {
    console.log(req.body);
    next();
  },
  genSeq
);

module.exports = router;
