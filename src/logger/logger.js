'use strict';

const path = require('path');
const winston = require('winston');

const errorFile = new winston.transports.File({
  level: 'warn',
  format: winston.format.json(),
  filename: path.join(__dirname, '..', '..', 'logs', 'express.log')
});

const infoConsole = new winston.transports.Console({
  level: 'info',
  format:
    process.env.NODE_ENV === 'production'
      ? winston.format.padLevels()
      : winston.format.cli()
});

const logger = winston.createLogger({
  transports: [errorFile, infoConsole]
});

module.exports = logger;
