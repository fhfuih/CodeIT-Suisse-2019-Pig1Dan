const router = require('express').Router();

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

module.exports = router;
