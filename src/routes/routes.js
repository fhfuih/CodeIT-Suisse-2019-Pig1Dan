const router = require('express').Router();

const logger = require('../logger/logger');
const helloWorldCpp = require('../controller/helloWorldCpp');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.get('/hellocpp', helloWorldCpp);

router.post('/sort', (req, res) => {
  logger.info(`/sort Payload is "${JSON.stringify(req.body)}"`);
  res.json([]);
});

router.post('/square', (req, res) => {
  logger.info(`/square Payload is "${JSON.stringify(req.body)}"`);
  res.json([]);
});

module.exports = router;
