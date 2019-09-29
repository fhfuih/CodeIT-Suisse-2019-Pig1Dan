
var ml = require('ml-sentiment');
var http = require('http');
var querystring =require('querystring');
var axios = require('axios');

async function sentiment(req, res) {
  const {
    reviews,
  } = req.body;
  // const senti = new Sentiment();
  const docs = [];
  const results = [];
  for (let i = 0; i < reviews.length; i += 1) {
    const doc = {
      language: 'en',
      id: (i + 1),
      text: reviews[i]
    };
    docs.push(doc);
  }
  // const body = {
  //   documents: docs
  // }
  await axios({
    method: 'post',
    url: 'https://westcentralus.api.cognitive.microsoft.com/text/analytics/v2.1/sentiment',
    headers: {
      'Content-Type': 'application/json',
      'Accept': 'application/json',
      'Ocp-Apim-Subscription-Key': '40bb5e9a13ef42c48df953873e366ef7'
    },
    data: {
      documents: docs
    }
  }).then(function (res) {
    // console.log(res.data);
    const replies = res.data.documents;
    console.log(replies);
    for (let i = 0; i < replies.length; i += 1) {
      results.push(replies[i].score > 0.64 ? 'positive' : 'negative');
    }
  });
  console.log(results);
  // var postData = JSON.stringify(body);
  // console.log(postData);
  // var options = {
  //   method: 'POST',
  //   host: 'westcentralus.api.cognitive.microsoft.com',
  //   path: '/text/analytics/v2.1/sentiment',
  //   headers: {
  //     'Content-Type': 'application/json',
  //     'Accept': 'application/json',
  //     'Ocp-Apim-Subscription-Key': '40bb5e9a13ef42c48df953873e366ef7'
  //   }
  // };
  // var request = http.request(options, function(res) {
  //   console.log('STATUS:', res.statusCode);
  // });
  // request.write(postData);
  // request.end();
  res.send({
    response: results
  });
}

module.exports = sentiment;
