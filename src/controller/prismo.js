
function find1D(arr) {
  for (let i = 0; i < arr.length; i += 1) {
    if (arr[i] === 0) {
      return i;
    }
  }
}
function prismo (req, res) {
  const {
    initial,
    goal
  } = req.body;
  const moves = [];
  if (initial.length) {
    if (initial[0].length) {

    } else {
      let xO = find1D(initial);
      const xT = find1D(goal);
      while (xO !== xT) {
        if (xO > xT) {
          xO -= 1;
          moves.push('L');
        } else if (xO < xT) {
          xO += 1;
          moves.push('R');
        }
      }
    }
  }
  res.send({
    moves: moves
  })
}

module.exports = prismo;
