const router = require('express').Router();

const logger = require('../logger/logger');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.post('/sort', (req, res) => {
  logger.info(`/sort Payload is "${JSON.stringify(req.body)}"`);
  res.json([]);
});

router.post('/square', (req, res) => {
  logger.info(`/square Payload is "${JSON.stringify(req.body)}"`);
  res.json([]);
});

module.exports = router;
