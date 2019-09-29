const router = require('express-promise-router')();

const sort = require('../controller/sort');
const square = require('../controller/square');
const genSeq = require('../controller/generateSequence');
const lottery = require('../controller/reverseLottery');
const chessGame = require('../controller/chessgame');
const readyPlayerOne = require('../controller/readyplayerone');
const wedNightmare = require('../controller/wedNightmare');
const typingContest = require('../controller/typingContest');
const wedding_cpp = require('../controller/wedding_cpp')
const gun = require('../controller/gun');
const sentiment = require('../controller/sentiment');
const portfolio = require('../controller/portfolio');
const portfolio1b = require('../controller/portfolio1b');
const portfolio1c = require('../controller/portfolio1c');
const portfolio4 = require('../controller/portfolio4');
const prismo = require('../controller/prismo');
const prismo_cpp = require('../controller/prismo_cpp');
const exponent = require('../controller/exponent');
const composition = require('../controller/composition');
const defuse = require('../controller/defuse');
const yin_yang = require('../controller/yin_yang');
const bucketFill = require('../controller/bucketFill');
const bucketFillCpp = require('../controller/bucketFillCpp');
const bankBranch = require('../controller/bankBranch');
const secretMessage = require('../controller/secretMessage');
// const techana = require('../controller/technicalAnalysis');
const techana = require('../controller/technicalCpp');
const fs = require('fs');

router.get('/hello', (req, res) => {
  const { name = 'world' } = req.query;
  res.send(`hello ${name}!`);
});

router.get('/lottery', lottery);

router.post('/sort', sort);

router.post('/square', square);

router.post('/generateSequence', genSeq);

router.post('/chessgame', chessGame);

router.post('/gun-control', gun);

router.post('/wedding-nightmare', (req, res, next) => {
  // console.log('Payload is', req.body);
  // fs.writeFile(__dirname + '/wnight.log', JSON.stringify(req.body), (err) => err ? console.log('err on log wnight') : console.log('saved to wnignt.log'))
  // fs.writeFile(JSON.stringify(req.body, __dirname + '/wnight.log'));
  next();
}, wedding_cpp);

router.post('/typing-contest', (req, res, next) => {
  console.log('Payload is', req.body);
  next();
}, typingContest);

router.post('/readyplayerone', (req, res, next) => {
  console.log('Payload is', req.body);
  next();
}, readyPlayerOne);

// router.post('/wedding-nightmare', (req, res, next) => {
//   const cases = req.body;
//   fs.writeFile("./input.txt", JSON.stringify(cases, null, "\t"), function(err) {
//     if(err) {
//         return console.log(err);
//     }
//     console.log("The file was saved!");
//   });
//   wedNightmare(req, res);
// });

// router.post('/sentiment-analysis', sentiment);

router.post('/maximise_1a', (req, res, next) => {
  console.log('Maximise Payload is', req.body);
  fs.writeFile(`./Maximise${Date.now()}.txt`, JSON.stringify(req.body), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The file was saved!");
  });
  next();
},  portfolio);

router.post('/maximise_1b', portfolio1b);

router.post('/maximise_1c', portfolio1c);

router.post('/maximise_2', portfolio4);

router.post('/composition', (req, res, next) => {
  console.log('Composition Payload is', req.body);
  fs.writeFile("./comp.txt", JSON.stringify(req.body), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The file was saved!");
  });
  next();
}, composition);

// router.post('/prismo', prismo);

router.post('/exponent', exponent);

router.post('/sentiment-analysis', (req, res, next) => {
  const {reviews} = req.body;
  fs.writeFile("./input.txt", JSON.stringify(reviews, null, "\t"), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The file was saved!");
  });
  sentiment(req, res);
});

router.post('/defuse', (req, res, next) => {
  console.log('Payload is', req.body);
  next();
}, defuse);

router.post('/yin-yang', (req, res, next) => {
  console.log('Payload is', req.body);
  next();
}, yin_yang);

router.post('/prismo', (req, res, next) => {
  console.log('Composition Payload is', req.body);
  fs.writeFile("./prismo.txt", JSON.stringify(req.body), function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The file was saved!");
  });
  next();
}, prismo_cpp);

router.post('/bucket-fill', (req, res, next) => {
  fs.writeFile("./input.txt", req.body, function(err) {
    if(err) {
        return console.log(err);
    }
    console.log("The file was saved!");
  });
  bucketFillCpp(req, res);
});

router.post('/bankbranch', (req, res, next) => {
  console.log('Payload is', req.body);
  next();
}, bankBranch);

router.post('/encryption', secretMessage);

router.post('/technical-analysis', (req, res, next) => {
  console.log('Payload is', req.body);
  next();
}, techana);

module.exports = router;
