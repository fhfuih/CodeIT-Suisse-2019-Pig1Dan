function square (req, res) {
  const { input } = req.body;
  console.log(input);
  res.send((input * input).toString());
}

module.exports = square;
