function checkBorder(board, x, y) {
  if (x < 0 || x > board.length - 1) {
    return true;
  }
  if (y < 0 || y > board.length - 1) {
    return true;
  }
}
function chessGame(req, res) {
  const board = req.body;
  let num = 0;
  let kX = 0;
  let kY = 0;
  for (let i in board) {
    for (let j in board) {
      if (board[i][j] === 'K') {
        kX = parseInt(j);
        kY = parseInt(i);
      }
    }
  }
  const direct = [
    [1, 0],
    [0, 1],
    [1, 1],
    [1, -1]
  ];
  for (let i in direct) {
    let locLX = kX;
    let locRX = kX;
    let locLY = kY;
    let locRY = kY;
    let obstL = false;
    let obstR = false;
    while ((locLX >= 0 && locLY >= 0 && locLY <= board.length - 1) || (locRX <= board.length - 1 && locRY >= 0 && locRY <= board.length - 1)) {
      if ((locLX >= 0 && locLY >= 0 && locLY <= board.length - 1)) {
        locLX -= direct[i][0];
        locLY -= direct[i][1];
      }
      if ((locRX >= 0 && locRY >= 0 && locRY <= board.length - 1)) {
        locRX += direct[i][0];
        locRY += direct[i][1];
      }
      if (!checkBorder(board, locLX, locLY) && board[locLY][locLX] === 'X') {
        obstL = true;
      }
      if (!checkBorder(board, locRX, locRY) && board[locRY][locRX] === 'X') {
        obstR = true;
      }
      if (obstR && obstL) {
        break;
      } else {
        if (!obstL && !checkBorder(board, locLX, locLY)) {
          num += 1;
        }
        if (!obstR && !checkBorder(board, locRX, locRY)) {
          num += 1;
        }
      }
    }
  }
  res.send(num.toString());
}

module.exports = chessGame;
