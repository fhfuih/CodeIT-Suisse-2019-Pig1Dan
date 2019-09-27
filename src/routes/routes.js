const router = require('express-promise-router')();

const logger = require('../logger/logger');
const sort = require('../controller/sort');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.post('/sort', sort);

router.post('/square', (req, res) => {
  logger.info(`/square Payload is "${JSON.stringify(req.body)}"`);
  res.json([]);
});

module.exports = router;
