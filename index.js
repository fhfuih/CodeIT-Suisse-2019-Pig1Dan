'use strict';

require('dotenv').config();

const express = require('express');

/* Middlewares */
const bodyParser = require('body-parser');
const cors = require('cors');
const helmet = require('helmet');
const morgan = require('morgan');

const router = require('./src/routes/routes');
const logger = require('./src/logger/logger');
const errorResponse = require('./src/responses/errorResponse');

const app = express();
const port = process.env.PORT || 3000;
const ip = process.env.IP || '127.0.0.1';

/* CORS */
app.use(cors()); // allow all CORS
app.options('*', cors()); // allow pre-flight

/* POST form parser */
app.use(bodyParser.json({ strict: false, limit: '50mb' }));
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.text({ type: ['text/plain', 'image/svg+xml'] }));

/* security */
app.use(helmet());

/* logger */
app.use(
  morgan('combined', {
    stream: {
      write: message => logger.info(message)
    }
  })
);

/* routes */
app.use(router);

/* errors */
app.use((err, req, res, next) => {
  logger.warn(err);
  res.status(500).json(
    errorResponse({
      message: 'Internal Server Error'
    })
  );
});

app.use((req, res) => {
  res.status(400).json(
    errorResponse({
      message: 'Bad Request'
    })
  );
});

app.listen(port, ip, () => {
  logger.info(`App listening on ${ip}:${port}`);
});
