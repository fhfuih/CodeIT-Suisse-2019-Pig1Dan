function square (req, res) {
  const { input } = req.body;
  console.log(input);
  res.send({
    ans: input * input
  });
}

module.exports = square;
