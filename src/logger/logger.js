'use strict';

const path = require('path');
const winston = require('winston');

function prodFormat() {
  const replaceError = ({ label, level, message, stack, query, ip }) => ({
    label,
    level,
    message,
    stack,
    query,
    ip
  });
  const replacer = (key, value) =>
    value instanceof Error ? replaceError(value) : value;
  return winston.format.json({ replacer });
}

function devFormat() {
  const formatMessage = info => `${info.level} ${info.message}`;
  const formatError = info => `${info.level} ${info.message}\n${info.stack}`;

  const format = info =>
    info instanceof Error ? formatError(info) : formatMessage(info);
  return winston.format.combine(
    winston.format.colorize(),
    winston.format.printf(format)
  );
}

const errorFile = new winston.transports.File({
  level: 'warn',
  format: prodFormat(),
  filename: path.join(__dirname, '..', '..', 'logs', 'express.log')
});

const infoConsole = new winston.transports.Console({
  level: 'info',
  format: process.env.NODE_ENV === 'production' ? prodFormat() : devFormat()
});

const logger = winston.createLogger({
  transports: [errorFile, infoConsole]
});

module.exports = logger;
